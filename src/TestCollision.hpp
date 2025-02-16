/**
 * @file TestCollision.hpp
 * @author Xein
 * @date 01/02/25
 *
 * @brief [Brief description of the file's purpose]
 */
#pragma once
#include <pch.hpp>
#include "Objects/Character.hpp"

namespace game {

class TestCollision : public Sigma::Character {
public:
  explicit TestCollision(const Sigma::id_t id) : Character(id) {}

  void Init() override {}
  void Start() override;
  void Update(double delta) override {}
  void Destroy() override {}

  void OnDamage(const Sigma::Damage::DamageEvent &e) override;
};
}
