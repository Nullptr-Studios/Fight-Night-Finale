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

  glm::vec3 offset = {-280, 190, 0};

  void Update(int healthvalue, int healthrecover){

    int value = glm::clamp(healthvalue, 0, 99);

    currentHealth[0]->Change(value/10);
    currentHealth[1]->Change(value%10);

    blue->m_currentHealth = glm::floor(healthrecover);
    health->m_currentHealth = glm::floor(healthvalue); 
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

  UIHealthBar player1 = {};
  UIHealthBar player2 = {};

  std::array<PlayerStruct, 2>* m_players;
};

}

