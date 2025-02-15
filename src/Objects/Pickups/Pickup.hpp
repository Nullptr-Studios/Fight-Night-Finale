
/**
 * @file Pickup.hpp
 * @author Alexey
 * @date 15/02/2025
 *
 * @brief Main class for a pickup object
 */
#pragma once

#include "Objects/Actor.hpp"
#include "Collision/CollisionEvent.hpp"
#include "Player/Player.hpp"

namespace game {
class Pickup : public Sigma::Actor {

public:
    explicit Pickup(Sigma::id_t id) : Actor(id) {}
    ~Pickup() override = default;

    void Start() override;
    bool OnCollision(Sigma::Collision::CollisionEvent &e) override;

protected:
  float m_healAmount = 50; ///>@brief amount to heal the player
  };
}