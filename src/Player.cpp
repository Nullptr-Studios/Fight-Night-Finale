#include "Player.hpp"

namespace game {

void Player::Init() { m_controllerComponent = std::make_unique<FNFE::PlayerController>(this); }

void Player::Start() {}

void Player::Update(double delta) {}

void Player::Destroy() {}

} // namespace game
