/**
 * @file Player.cpp
 * @author Xein
 * @date 30/01/2025
 *
 * @brief Main class for the player
 */

#pragma once
#include <UI/DeadMenu.hpp>
#include <pch.hpp>

#include "Objects/Character.hpp"
#include "PlayerController.hpp"
#include "UI/HUD.hpp"

namespace game {
class GameplayManager;
}
namespace game {
class MainMenu;

class Player : public Sigma::Character {
public:
  
  /**
   * @brief Construct a Player object
   *
   * @param id
   * @param controllerId
   */
  explicit Player(const Sigma::id_t id, int controllerId, std::string jsonPath) : Character(id, std::move(jsonPath)), m_controllerId(controllerId) {}

  void Init() override;
  void Serialize() override;
  void Start() override;
  void Update(double delta) override;
  void Destroy() override;
  void SetControllerID(int id);
  int GetControllerID() const { return m_controllerId; }

  void OnDamage(const Sigma::Damage::DamageEvent &e) override;
  void OnHeal(float health) { 
    SetHealth(m_health + health); 
    healthBar->Update(GetHealth<int>(), m_healthRecover);
  }
  game::UIHealthBar* healthBar = nullptr;

  void DoSuperAttack() override;
  void RegainHPCombo() override;

private:
  /// @brief Holds the Player Controller Component to handle input
  std::unique_ptr<PlayerController> m_controllerComponent = nullptr;

  int m_controllerId;

  int m_healthRecover = 75;

  Sigma::Actor* m_debugPlayerCol = nullptr;
  MainMenu *m_deadScene = nullptr;

  bool doFuckingOnce = true;
  
};

} // namespace game
