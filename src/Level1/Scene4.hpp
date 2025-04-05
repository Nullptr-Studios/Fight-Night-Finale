/**
 * @file Scene4.hpp
 * @author Xein
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

class Scene4 : public game::GameScene {
public:
  Scene4(const char *name, unsigned ID, const char *jsonPath) :
      GameScene(name, ID, jsonPath) {}

  void Load() override;

  void Update(double delta) override;
  void Free() override;


private:
  std::shared_ptr<Sigma::Actor> floor = nullptr;
  std::shared_ptr<Sigma::Actor> walls = nullptr;

};

} // namespace game
