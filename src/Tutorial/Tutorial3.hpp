/**
 * @file Tutorial_3.hpp
 * @author Xein
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

class Tutorial3 : public game::GameScene {
public:
  Tutorial3(const char *name, unsigned ID, const char *jsonPath) :
      GameScene(name, ID, jsonPath) {}

  void Load() override;

  void Update(double delta) override;
  void Free() override;

private:
  Sigma::Actor* background = nullptr;

protected:
  bool m_debug = true;
};

} // namespace game
