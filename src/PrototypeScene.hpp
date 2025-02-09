/**
 * @file PrototypeScene.hpp
 * @author Xein
 * @date 29/01/2025
 *
 * @brief A scene made for testing things of the game
 */

#pragma once
#include "Scene.hpp"

namespace game {

class PrototypeScene : public Sigma::Scene {
public:
  PrototypeScene(const char *name, unsigned index) : Scene(name, index) {}

  void Load() override;
  void Update(double delta) override {}
  void Draw() override {}
};

} // namespace game
