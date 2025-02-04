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
  explicit Player(const Sigma::id_t id) : Character(id) {}

  void Init() override {};
  void Start() override;
  void Update(double delta) override;
  void Destroy() override;

private:
  /// @brief Holds the Player Controller Component to handle input
  std::unique_ptr<PlayerController> m_controllerComponent = nullptr;
};

} // namespace game
