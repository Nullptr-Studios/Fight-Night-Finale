//
// Created by Alexey on 11/02/2025.
//
#pragma once

#include "Objects/Actor.hpp"
#include "Collision/CollisionEvent.hpp"
#include "Player/Player.hpp"

namespace game {
class Pickup : public Sigma::Actor {

public:
    explicit Pickup(Sigma::id_t id) : Actor(id) {};
    ~Pickup() override = default;

    bool OnCollision(Sigma::Collision::CollisionEvent &e) override;

protected:
  float m_healAmount = 50.0f;

  };
}