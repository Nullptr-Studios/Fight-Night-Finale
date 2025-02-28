/**
 * @file Scene7.hpp
 * @author Alexey
 * @date 28/02/25
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

class Scene7 : public game::GameScene {
public:
  Scene7(const char *name, unsigned ID, const char *jsonPath) :
      GameScene(name, ID, jsonPath) {}

  void Load() override;

  void Update(double delta) override;
  void Free() override;

  std::array<Player*, 2> m_players = {};

private:
  Sigma::Actor* floor = nullptr;
  Sigma::Actor* walls = nullptr;

protected:
  bool m_debug = true;
};

} // namespace game
