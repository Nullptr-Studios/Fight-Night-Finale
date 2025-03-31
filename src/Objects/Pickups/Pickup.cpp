//
// Created by Alexey on 13/02/2025.
//

#include "Pickup.hpp"
#include "Factory.hpp"

namespace game {

void Pickup::Init() {
  Actor::Init();
  m_collider = std::make_unique<Sigma::Collision::BoxCollider>(Sigma::Collision::PLAYER, Sigma::Collision::COLLISION);
  m_collider->enabled = false;
}

void Pickup::Start() {
  Actor::Start();

  m_collider->enabled = true;
}

void Pickup::SetColSize(glm::vec3 colSize) {
  m_collider->box.Set(colSize);
}

void Pickup::SetHeal(float health) {
  m_healAmount = health;
}

bool Pickup::OnCollision(Sigma::Collision::CollisionEvent &e) {
  try {
    
 
  if (const auto player = dynamic_cast<Player*>(e.GetOther())) {
    player->OnHeal(m_healAmount);
    GET_FACTORY->DestroyObject(GetId());
    return true;
  }

  return false;
  } catch (const std::exception& e) {
    std::cerr << e.what() << std::endl;
    return false;
  }
  return false;
}

}
