#include "Player.hpp"
#include "Collision/Collider.hpp"
#include "Collision/CollisionEvent.hpp"

namespace game {

void Player::Start() {
  Character::Start();
  m_controllerComponent = std::make_unique<PlayerController>(this);
  m_controllerComponent->GetControllerID();

  m_collider = std::make_unique<Sigma::Collision::BoxCollider>(Sigma::Collision::PLAYER, Sigma::Collision::COLLISION);
  m_collider->box.Set(50, 50, 50, 50);
}

void Player::Update(double delta) {
  Character::Update(delta);
  if (m_controllerComponent) m_controllerComponent->Update();
}

void Player::Destroy() {}

bool Player::OnCollision(Sigma::Collision::CollisionEvent& e) {
  std::cout << "Collision with " << e.GetOther()->GetName() << "\n";
  return true;
}

} // namespace game