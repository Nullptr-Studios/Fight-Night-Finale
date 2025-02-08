#include "Player.hpp"
#include "Collision/Collider.hpp"
#include "Collision/CollisionEvent.hpp"

namespace game {

void Player::Init() {}

void Player::Start() {
  m_controllerComponent = std::make_unique<PlayerController>(this);
  m_controllerComponent->GetControllerID();

  m_collider = std::make_unique<Sigma::Collision::BoxCollider>(Sigma::Collision::PLAYER, Sigma::Collision::COLLISION);
  m_collider->box.Set(50, 50, 50, 50);
}

void Player::Update(double delta) {
  if (m_controllerComponent) m_controllerComponent->Update();
}

void Player::Destroy() {}

void Player::OnDamage(Sigma::Damage::DamageEvent& e) {
  Character::OnDamage(e);
  std::cout << "Damage with " << e.GetOther()->GetName() << "\n";
  std::cout << GetHealth() << "\n";
}

} // namespace game