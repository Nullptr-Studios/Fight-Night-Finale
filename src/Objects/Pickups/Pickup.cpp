//
// Created by Alexey on 13/02/2025.
//

#include "Pickup.hpp"
#include "Factory.hpp"

namespace game {

void Pickup::Init() {
  Actor::Init();
  m_collider = std::make_unique<Sigma::Collision::BoxCollider>(Sigma::Collision::PLAYER, Sigma::Collision::COLLISION);
  m_collider->box.Set({25,25,25});
}

bool Pickup::OnCollision(Sigma::Collision::CollisionEvent &e){
  //TODO: OnCollision function not being called for some reason...
  if (auto player = dynamic_cast<Player*>(e.GetOther())) {
    player->OnHeal(m_healAmount);
    GET_FACTORY->DestroyObject(GetId());
    return true;
  }
  return false;
}

}