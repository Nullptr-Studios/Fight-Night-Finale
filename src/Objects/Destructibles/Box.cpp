//
// Created by Alexey on 15/02/2025.
//

#include "Box.hpp"
#include "Core.hpp"
#include "Factory.hpp"
#include "Objects/Pickups/Pickup.hpp"

namespace game {
void Box::Init() {
  // Calls actor init because we don't need the default collider in damageable
  Sigma::Damageable::Init();

  m_animComp = new Sigma::Animation::AnimationComponent(this);

  auto t = GET_ANIMATION->LoadTextureAtlas("assets/objects/SlotMachine.json");
  m_animComp->SetTextureAtlas(t);
  SetTexture(t->textureStr.c_str());
  m_animComp->SetCurrentAnim("SlotMachine");
  m_animComp->GotoFrame(0);

  // Setting Variables

  // transform.scale = {m_size.x, m_size.y};
  m_collider = std::make_unique<Sigma::Collision::BoxCollider>(Sigma::Collision::PLAYER, Sigma::Collision::COLLISION);
  m_collider->box.Set(m_size);

  SetMaxHealth(1);
}
void Box::Update(double deltaTime) {
  Damageable::Update(deltaTime);

  if (m_animComp)
    m_animComp->Update(deltaTime);
}

void Box::OnDed() {
  m_collider->enabled = false;
  m_animComp->GotoFrame(1);
  // SetActive(false);
  auto Pi = GET_FACTORY->CreateObject<Pickup>("Pickup");
  Pi->SetColSize(m_pickupSize);
  Pi->SetHeal(m_pickupHeal);
  Pi->SetTexture(m_pickupTexture);
  Pi->transform.scale = {m_pickupSize.x, m_pickupSize.y};
  Pi->transform.position = transform.position;
  m_pickup = Pi;
}
void Box::Destroy() {
  Damageable::Destroy();
  
  if (m_pickup)
    GET_FACTORY->DestroyObject(m_pickup);
}

} // namespace game
