/**
 * @file Pickup.hpp
 * @author Alexey
 * @date 15/02/2025
 *
 * @brief class for a pickup object
 */
#pragma once

#include "Objects/Actor.hpp"
#include "Collision/CollisionEvent.hpp"
#include "Player/Player.hpp"

namespace game {
class Pickup : public Sigma::Actor {

public:
    explicit Pickup(Sigma::id_t id) : Actor(id){};
    ~Pickup() override = default;

    void Init() override;
    void Start() override;
    void SetHeal(float health);
    void SetColSize(glm::vec3 colSize);
    bool OnCollision(Sigma::Collision::CollisionEvent &e) override;

protected:
  float m_healAmount; ///>@brief amount to heal the player
  };
}
