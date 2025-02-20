/**
 * @file PrototypeScene.hpp
 * @author Xein
 * @date 29/01/2025
 *
 * @brief A scene made for testing things of the game
 */

#pragma once
#include <list>


#include "GameScene.hpp"

namespace Sigma {
class Actor;
class Object;
}
namespace game {
class Player;
class PunchingBag;
class HealthBar;
class Box;

class PrototypeScene : public game::GameScene {
public:
  PrototypeScene(const char *name, unsigned ID, const char *jsonPath) :
      GameScene(name, ID, jsonPath), floor(nullptr), walls(nullptr), healthBar(nullptr), s(nullptr), s2(nullptr),
      s3(nullptr), p(nullptr) {}

  void Load() override;

  void Update(double delta) override;
  void Free() override;

  std::list<Sigma::Object *> m_players;

private:
  Sigma::Actor *floor;
  Sigma::Actor *walls;
  HealthBar *healthBar;
  PunchingBag *s;
  PunchingBag *s2;
  PunchingBag *s3;
  HealthBar *healthBar2 = nullptr;
  Player *p;
  Player *p2 = nullptr;
  Box * b1;
};

} // namespace game
