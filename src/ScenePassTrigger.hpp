/**
 * @file ScenePassTrigger.hpp
 * @author Missing Textures
 * @date 01/04/25
 *
 * @brief [TODO: Brief description of the file's purpose]
 */

#pragma once

#include "Objects/Object.hpp"
namespace game{
class ScenePassTrigger : public Sigma::Object {
  
  void Init() override;
  void Update(double deltaTime) override;
  bool OnCollision(Sigma::Collision::CollisionEvent& e) override;
};

}
