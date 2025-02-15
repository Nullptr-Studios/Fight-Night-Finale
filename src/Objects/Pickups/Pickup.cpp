//
// Created by Alexey on 13/02/2025.
//

#include "Pickup.hpp"

namespace game {

void Pickup::Start() {
  m_collider = std::make_unique<Sigma::Collision::BoxCollider>(Sigma::Collision::PLAYER, Sigma::Collision::COLLISION);
  m_collider->box.Set({25,25});
}

bool Pickup:: OnCollision(Sigma::Collision::CollisionEvent &e){
  if (auto player = dynamic_cast<Player*>(e.GetOther())) {
    player->OnHeal(m_healAmount);
    SetActive(false);
    return true;
  }
  return false;
}

}