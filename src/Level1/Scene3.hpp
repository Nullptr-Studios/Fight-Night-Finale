/**
 * @file Scene3.hpp
 * @author Alexey
 * @date 28/02/25
 *
 * @brief [TODO: Brief description of the file's purpose]
 */
#pragma once

#include "GameScene.hpp"

namespace Sigma {
class Actor;
class Object;
}

namespace game {

class Scene3 : public game::GameScene {
public:
  Scene3(const char *name, unsigned ID, const char *jsonPath) :
      GameScene(name, ID, jsonPath) {}

  void Load() override;

  void Update(double delta) override;
  void Free() override;

private:
  Sigma::Actor* floor = nullptr;
  Sigma::Actor* walls = nullptr;

protected:
  bool m_debug = true;
};

} // namespace game
