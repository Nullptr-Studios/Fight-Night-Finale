/**
 * @file Tutorial_1.hpp
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

class Tutorial1 : public game::GameScene {
public:
  Tutorial1(const char *name, unsigned ID, const char *jsonPath) :
      GameScene(name, ID, jsonPath) {}

  void Load() override;

  void Update(double delta) override;
  void Free() override;

private:
  Sigma::Actor* m_background = nullptr;
  GameScene* m_nextScene = nullptr;

protected:
  bool m_debug = true;
};

} // namespace game
