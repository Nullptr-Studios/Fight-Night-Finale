/**
 * @file PrototypeScene.hpp
 * @author Xein
 * @date 29/01/2025
 *
 * @brief A scene made for testing things of the game
 */

#pragma once
#include "GameScene.hpp"

namespace game {

class PrototypeScene : public Sigma::GameScene {
public:
  PrototypeScene(const char *name, unsigned ID, const char *jsonPath) : GameScene(name, ID, jsonPath) {}

  void Load() override;

  void Update(double delta) override;
};

} // namespace game
