#include "Player.hpp"

namespace game {

void Player::Init() {
}

void Player::Start() {
  m_controllerComponent = std::make_unique<PlayerController>(this);
}

void Player::Update(double delta) {
  if (m_controllerComponent != nullptr) {
    m_controllerComponent->Update();
  }
}

void Player::Destroy() {
  delete m_controllerComponent;
}

} // namespace game
