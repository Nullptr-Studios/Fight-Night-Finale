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
public:
  explicit ScenePassTrigger(size_t id) : Object(id) {}

  
  void Init() override;
  bool OnCollision(Sigma::Collision::CollisionEvent& e) override;
};

}
