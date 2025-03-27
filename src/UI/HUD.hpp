/**
 * @file HUD.hpp
 * @author Xein
 * @date 03/03/25
 *
 * @brief [TODO: Brief description of the file's purpose]
 */
#pragma once
#include "Core.hpp"
#include "Objects/Manager/GameplayManager.hpp"

#include "UI/UIImage.hpp"
#include "UI/UINumber.hpp"
#include "UI/UIText.hpp"
#include "UI/HealthBar.hpp"
#include "Objects/Object.hpp"

namespace game {

class Player;

struct UIHealthBar {
  Sigma::UIImage* background = nullptr;
  HealthBar* blue = nullptr;
  HealthBar* health = nullptr;
  Sigma::UIImage* border = nullptr;

  Sigma::UIImage* frame = nullptr;
 
  std::array<Sigma::UINumber*, 2> currentHealth = {};
  std::array<Sigma::UINumber*, 2> maxHealth = {};
  Sigma::UIText* slash = nullptr;

  glm::vec3 offset = {-280, 450, 0};

  void Update(int healthvalue, int healthrecover){

    int value = glm::clamp(healthvalue, 0, 99);

    currentHealth[0]->Change(value/10);
    currentHealth[1]->Change(value%10);

    blue->m_currentHealth = glm::floor(healthrecover);
    health->m_currentHealth = glm::floor(healthvalue); 
  }
};

struct UIMoneyBar {

  static constexpr short maxDigits = 7; ///>@brief Max amount of digits displayable
  int maxCash; ///>@brief Max amount cash displayable, dependent on maxDigits
  int startCash = 0; ///>@brief Cash with which linear interpolation starts
  int endCash = 0; ///>@brief Cash with which linear interpolation ends
  int displayedCash = 0; ///>@brief Cash currently displayed

  bool active = false;

  double timerMax = 1.f; //Max time on lerp
  double timer = 0.0f; //Timer for time-based lerp or whatever the fuck idk what I'm doing rn tbh I want to sleep I'm so done.

  std::vector<Sigma::UINumber *> numbers = {};
  Sigma::UIElement* cashIcon = nullptr;

  glm::vec2 numScale = {54,63};
  glm::vec3 offset = {0,461,0};
  float leftX = 0; ///>@brief Left-most coordinate of the money display

  void DisplayMoney(int val) {
    if (val == displayedCash) 
      return; 

    displayedCash = val;
    for (int i = 0; i < maxDigits; i++) {
      int currentVal = displayedCash % static_cast<int>(pow(10, maxDigits-i)) / static_cast<int>(pow(10, maxDigits-i-1));
      numbers[i]->Change(currentVal);
    }
  }

  int LerpMoney(const double delta) {
    timer += delta;
    if (timer > timerMax) {
      timer = 0.0f;
      return endCash;
    }
    return round(std::lerp(startCash, endCash, timer * 1/timerMax));
  }

};

class HUD : public Sigma::Object {
public:
  explicit HUD(const Sigma::id_t id) : Object(id) {}

  void Init() override;
  void Start() override;
  void Update(double delta) override;
  void SetPlayer1Health(int health);

  void Enable();
  void Disable();

  void UpdateXP(int currentXP);

  void UpdatePlayerHUD();
  
  void EnableGOIndicator();
private:

  void SetNumbers(std::array<Sigma::UINumber*, 2> numbers, int value);

  float m_goMaxTimer = 3.0f;
  float m_goTimer = 0.0f;
  float m_goTimeFlash = .5f;
  float m_goTimerFlash = 0.0f;
  bool m_goActive = false;

  Sigma::UIImage* m_goIndicator = nullptr;

  void EnableUIPlayer1(bool enable);
  void EnableUIPlayer2(bool enable);
  void EnableUIMoney(bool enable);

  UIHealthBar player1 = {};
  UIHealthBar player2 = {};
  UIMoneyBar money = {};

  std::array<PlayerStruct, 2>* m_players;
};

}

