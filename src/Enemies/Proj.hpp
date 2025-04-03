/**
 * @file Proj.hpp
 * @author Dante Harper
 * @date 03/04/25
 *
 * @brief toast!
 */

#pragma once

#include "Objects/Actor.hpp"
namespace game {

class Proj : public Sigma::Actor {
public:
  explicit Proj(Sigma::id_t id) : Sigma::Actor(id) {};
  void Init() override;
  void Update(double delta) override;
  bool OnCollision(Sigma::Collision::CollisionEvent &e) override;
  glm::vec3 velocity{};
private:
  float m_damage = 10;
};
} // namespace game
