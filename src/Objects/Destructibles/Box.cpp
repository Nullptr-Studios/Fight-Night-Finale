//
// Created by Alexey on 15/02/2025.
//

#include "Box.hpp"
#include "Core.hpp"
#include "Factory.hpp"
#include "Objects/Pickups/Pickup.hpp"

namespace game {
void Box::Init() {
  //Calls actor init because we don't need the default collider in damageable
  Actor::Init();

  //Setting Variables
  transform.scale = {m_size.x, m_size.y};
  m_collider = std::make_unique<Sigma::Collision::BoxCollider>(Sigma::Collision::PLAYER, Sigma::Collision::COLLISION);
  m_collider->box.Set(m_size);
  SetMaxHealth(1);
  SetTexture(m_texture);
}

void Box::OnDed() {
  SetTexture(m_brokenTexture);
  m_collider->enabled = false;
  auto Pi = GET_FACTORY->CreateObject<Pickup>("Pickup");
  Pi->SetColSize(m_pickupSize);
  Pi->SetHeal(m_pickupHeal);
  Pi->SetTexture(m_pickupTexture);
  Pi->transform.scale = {m_pickupSize.x, m_pickupSize.y};
  Pi->transform.position = transform.position;
}

}
