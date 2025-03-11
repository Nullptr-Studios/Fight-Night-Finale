/**
 * @file Tutorial_2.hpp
 * @author Alexey
 * @date 10/03/25
 *
 * @brief [TODO: Brief description of the file's purpose]
 */
#pragma once

#include "GameScene.hpp"
#include "Player/Player.hpp"

namespace Sigma {
class Actor;
class Object;
}

namespace game {

class GlowArea;

class Tutorial2 : public game::GameScene {
public:
  Tutorial2(const char *name, unsigned ID, const char *jsonPath) :
      GameScene(name, ID, jsonPath) {}

  void Load() override;

  void Update(double delta) override;
  void Free() override;

private:
  Sigma::Actor* background = nullptr;
  GlowArea* m_glowArea = nullptr;

protected:
  bool m_debug = true;
};

} // namespace game
