#include "Player.hpp"
#include "Collision/Collider.hpp"

namespace game {

void Player::Init() {
  Character::Init();
}

void Player::Start() {
  Character::Start();
  m_controllerComponent = std::make_unique<PlayerController>(this);
  m_controllerComponent->GetControllerID();

  m_collider = std::make_unique<Sigma::Collision::BoxCollider>(Sigma::Collision::PLAYER, Sigma::Collision::COLLISION);
  m_collider->box.Set(transform.scale);
  m_collider->damage = 1.0f;
}

void Player::Update(double delta) {
  Character::Update(delta);
  if (m_controllerComponent && GetAlive()) m_controllerComponent->Update();
}

void Player::Destroy() {}

void Player::OnDamage(Sigma::Damage::DamageEvent& e) {
  Character::OnDamage(e);
  std::cout << "Damage with " << e.GetOther()->GetName() << "\n";
  std::cout << GetHealth() << "\n";
}

} // namespace game
