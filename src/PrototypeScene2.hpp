//
// Created by Alexey on 15/02/2025.
//

#pragma once
#include "GameScene.hpp"

namespace game {
class PrototypeScene2 : public Sigma::GameScene {
public:
  PrototypeScene2(const char *name, unsigned ID, const char *jsonPath) : GameScene(name, ID, jsonPath) {}

  void Load() override;
};
}
