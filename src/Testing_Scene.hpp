/**
 * @file Testing_Scene.hpp
 * @author Alexey
 * @date 29/01/2025
 *
 * @brief A scene made for testing level1 bounds
 */

#pragma once
#include "GameScene.hpp"
#include "Player/Player.hpp"

namespace Sigma {
class Actor;
class Object;
}
namespace game {
class PunchingBag;
class HealthBar;

class Testing_Scene : public game::GameScene {
public:
  Testing_Scene(const char *name, unsigned ID, const char *jsonPath) :
      GameScene(name, ID, jsonPath), floor(nullptr), walls(nullptr), healthBar(nullptr), p(nullptr) {}

  void Load() override;

  void Update(double delta) override;
  void Free() override;

  std::array<Player*, 2> m_players = {};

private:
  Sigma::Actor *floor;
  Sigma::Actor *walls;
  HealthBar *healthBar;
  HealthBar *healthBar2 = nullptr;
  Player *p;
  Player *p2 = nullptr;

  MainMenu* m_deadScene = nullptr;
};

} // namespace game
