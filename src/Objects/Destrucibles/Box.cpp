//
// Created by Alexey on 15/02/2025.
//

#include "Box.hpp"
#include "Core.hpp"
#include "Factory.hpp"
#include "Objects/Pickups/Pickup.hpp"

namespace game {
void Box::Init() {
  Actor::Init();
  m_collider = std::make_unique<Sigma::Collision::BoxCollider>(Sigma::Collision::PLAYER, Sigma::Collision::COLLISION);
  //TODO: tweak values to match texture
  m_collider->box.Set({64,64,160});
  SetMaxHealth(1);
}

void Box::OnDed() {
  SetTexture("assets/prototype-scene-2/Prototype_Box_Broken.png");
  m_collider->enabled = false;
  auto Pi = GET_FACTORY->CreateObject<Pickup>("Medkit");
  Pi->SetTexture("assets/prototype-scene-2/Medkit.png");
  Pi->transform.scale = {32.0f, 32.0f};
  Pi->transform.position = transform.position;
}

}
