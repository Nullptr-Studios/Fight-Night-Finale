#include "Player.hpp"

namespace game {

void Player::Init() {
}

void Player::Start() {
  m_controllerComponent = std::make_unique<PlayerController>(this);
  m_controllerComponent->GetControllerID();
}

void Player::Update(double delta) {
  if (m_controllerComponent) m_controllerComponent->Update();
}

void Player::Destroy() {
  m_controllerComponent.reset();
}
} // namespace game