/**
 * @file HUD.hpp
 * @author Xein
 * @date 03/03/25
 *
 * @brief [TODO: Brief description of the file's purpose]
 */
#pragma once
#include <memory>
#include <string>
#include "Core.hpp"
#include "Objects/Manager/GameplayManager.hpp"

#include "Objects/ShakeObject.hpp"
#include "UI/UIImage.hpp"
#include "UI/UIFade.hpp"
#include "UI/UINumber.hpp"
#include "UI/UIText.hpp"
#include "UI/HealthBar.hpp"
#include "Objects/Object.hpp"

#include "Objects/ShakeObject.hpp"

namespace game {

class Player;

enum ComboStreakClasification
{
  BAD = 5,
  GREAT = 10,
  SUPER = 20,
  AWESOME = 40,
  EXCELLENT = 60,
  RAMPAGE = 90
};

struct UIHealthBar {
  std::shared_ptr<Sigma::UIImage> background = nullptr;
  std::shared_ptr<HealthBar> blue = nullptr;
  std::shared_ptr<HealthBar> health = nullptr;
  std::shared_ptr<Sigma::UIImage> border = nullptr;

  std::shared_ptr<Sigma::UIImage> frame = nullptr;
  std::array<std::shared_ptr<Sigma::UINumber>, 2> currentHealth = {};
  std::array<std::shared_ptr<Sigma::UINumber>, 2> maxHealth = {};
  std::shared_ptr<Sigma::UIText> slash = nullptr;

  std::shared_ptr<Sigma::UIText> comboText = nullptr;
  Sigma::ShakeObject* comboShake = nullptr;

  glm::vec3 offset = {-280, 450, 0};

  short combo = 0;

  float m_comboSreakEnd = 3.0f;
  float m_comboDisapear = 5.0f;


  void ComboBreak() {
    combo = 0;
    m_comboDisapear = 5.0f;
    comboText->SetText("Break!!!");
    comboText->SetTint({.5f, 0.5f, 0.5f, 1.0f});
  }

  void ComboSuccesfull() const 
  {
    std::string str = std::to_string(combo) + " Hit Streak";
    std::string rating;

    glm::vec4 color = {1.0f, 1.0f, 1.0f, 1.0f};
    if(combo <= BAD){
      rating = "BAD\n";
      color = {1.0f, 0.0f, 0.0f, 1.0f};
    }else if(combo <= GREAT){
      rating = "GREAT\n";
      color = {1.0f, 1.0f, 0.0f, 1.0f};
    }else if(combo <= SUPER){
      rating = "SUPER!\n";
      color = {0.0f, 1.0f, 0.0f, 1.0f};
    }else if(combo <= AWESOME){
      rating = "AWESOME!!\n";
      color = {0.0f, 1.0f, 1.0f, 1.0f};
    }else if(combo <= EXCELLENT){
      rating = "EXCELLENT!!!\n";
      color = {0.0f, 0.0f, 1.0f, 1.0f};
    }else{
      rating = "RAMPAGE!!!!\n";
      color = {1.0f, 0.0f, 1.0f, 1.0f};
    }

    rating += str;
    comboText->SetTint(color);
    comboText->SetText(rating.c_str());
    comboShake->StartShake(1.5f, 60, 50, Sigma::ShakeType::EASE_OUT);

  }

  void StreakAdd(){
    combo++;
    m_comboDisapear = 5.0f;
    std::string s = "Streak ";
    s.append(std::to_string(combo));
    comboText->SetText(s.c_str());
    comboShake->StartShake(.5f, 60, 25, Sigma::ShakeType::EASE_OUT);
    comboText->SetTint({1.0f, 1.0f, 1.0f, 1.0f});
  }


  void Update(int healthvalue, int healthrecover){

    int value = glm::clamp(healthvalue, 0, 99);

    currentHealth[0]->Change(value/10);
    currentHealth[1]->Change(value%10);

    blue->m_currentHealth = glm::floor(healthrecover);
    health->m_currentHealth = glm::floor(healthvalue); 
  }
};

constexpr int pow(int base, int exp) {
  return (exp == 0) ? 1 : base * pow(base, exp - 1);
}

struct UIMoneyBar {

  static constexpr int maxDigits {7}; ///>@brief Max amount of digits displayable
  static constexpr int maxCash {pow(10, game::UIMoneyBar::maxDigits) - 1}; ///>@brief Max amount cash displayable, dependent on maxDigits
  int startCash = 0; ///>@brief Cash with which linear interpolation starts
  int endCash = 0; ///>@brief Cash with which linear interpolation ends
  int displayedCash = 0; ///>@brief Cash currently displayed

  bool active = false;

  double timerMax = 1.f; //Max time on lerp
  double timer = 0.0f; //Timer for time-based lerp or whatever the fuck idk what I'm doing rn tbh I want to sleep I'm so done.

  std::vector<Sigma::UINumber *> numbers = {};
  std::shared_ptr<Sigma::UIElement> cashIcon = nullptr;

  glm::vec2 numScale = {54,63};
  glm::vec3 offset = {0,461,0};
  static constexpr float leftX {-60.0f * game::UIMoneyBar::maxDigits / 2.0f}; ///>@brief Left-most coordinate of the money display

void DisplayMoney(int val) {
    if (val == displayedCash)
      return;

    displayedCash = val;
    int divisor = static_cast<int>(glm::pow(10, maxDigits - 1));
    for (int i = 0; i < maxDigits; i++) {
      int currentVal = (displayedCash / divisor) % 10;
      numbers[i]->Change(currentVal);
      divisor /= 10;
    }
  }


  int LerpMoney(const double delta) {
    timer += delta;
    if (timer > timerMax) {
      timer = 0.0f;
      return endCash;
    }
    return glm::round(std::lerp(startCash, endCash, timer * 1/timerMax));
  }

};

class HUD : public Sigma::Object {
public:
  explicit HUD(const Sigma::id_t id) : Object(id) {}
  ~HUD() override;

  void Init() override;
  void Start() override;
  void Update(double delta) override;

  void Enable();
  void Disable();

  void DoInitialSceneText(std::string text);

  void UpdateXP(int currentXP);

  void UpdatePlayerHUD();

  void SetNumbers(std::array<std::shared_ptr<Sigma::UINumber>, 2> numbers, int value);

  void EnableGOIndicator();

  
  std::shared_ptr<Sigma::UIFade> m_fadeScreen = nullptr;

private:

  float m_goMaxTimer = 3.0f;
  float m_goTimer = 0.0f;
  float m_goTimeFlash = .5f;
  float m_goTimerFlash = 0.0f;
  bool m_goActive = false;

  std::shared_ptr<Sigma::UIImage> m_goIndicator = nullptr;

  void EnableUIPlayer1(bool enable);
  void EnableUIPlayer2(bool enable);
  void EnableUIMoney(bool enable);

  UIHealthBar player1 = {};
  UIHealthBar player2 = {};
  UIMoneyBar money = {};


  std::array<PlayerStruct, 2>* m_players = {};
};

}

