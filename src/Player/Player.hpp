/**
 * @file Player.cpp
 * @author Xein
 * @date 30/01/2025
 *
 * @brief Main class for the player
 */

#pragma once
#include <pch.hpp>
#include "Objects/Character.hpp"
#include "PlayerController.hpp"

namespace game {

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
  void Start() override;
  void Update(double delta) override;
  void Destroy() override;

  void OnDamage(const Sigma::Damage::DamageEvent &e) override;;

private:
  /// @brief Holds the Player Controller Component to handle input
  std::unique_ptr<PlayerController> m_controllerComponent = nullptr;

  int m_controllerId = -1;
};

} // namespace game
