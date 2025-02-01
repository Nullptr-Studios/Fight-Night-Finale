/**
 * @file TestCollision.hpp
 * @author Xein
 * @date 01/02/25
 *
 * @brief [Brief description of the file's purpose]
 */
#pragma once
#include <pch.hpp>
#include <Objects/Actor.hpp>

namespace game {

class TestCollision : public sigma::Actor {
public:
  explicit TestCollision(const sigma::id_t id) : Actor(id) {}

  void Init() override {}
  void Start() override;
  void Update(double delta) override {}
  void Destroy() override {}
};
}
