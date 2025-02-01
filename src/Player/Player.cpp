#include "Player.hpp"
#include "Collision/Collider.hpp"
#include "Collision/CollisionEvent.hpp"

namespace game {

void Player::Init() {
}

void Player::Start() {
  m_controllerComponent = new PlayerController(this);
  m_collider = std::make_unique<sigma::Collision::BoxCollider>(sigma::Collision::PLAYER, sigma::Collision::COLLISION);
  m_collider->box.Set(50, 50, 50, 50);
}

void Player::Update(double delta) {
  if (m_controllerComponent != nullptr) {
    m_controllerComponent->Update();
  }
}

void Player::Destroy() { delete m_controllerComponent; }

bool Player::OnCollision(sigma::Collision::CollisionEvent& e) {
  std::cout << "Collision with " << e.GetOther()->GetName() << "\n";
  return true;
}

} // namespace game
