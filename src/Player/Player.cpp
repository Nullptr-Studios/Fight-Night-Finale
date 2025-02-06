#include "Player.hpp"

namespace game {
void Player::Init() {
  Character::Init();
  
  transform.relativeScale = 3;
}

void Player::Start() {
  Character::Start();
  
  auto anim = GET_ANIMATION->LoadTextureAtlas("assets/Idle.json");
  m_animComp->SetTextureAtlas(anim);
  m_animComp->SetCurrentAnim("Default");
  SetTexture("assets/Idle.png");
  m_animComp->PlayAnim();
  
  m_controllerComponent = std::make_unique<PlayerController>(this);
  m_controllerComponent->GetControllerID();
}

void Player::Update(double delta) {
  Character::Update(delta);
  if (m_controllerComponent) m_controllerComponent->Update();
}

void Player::Destroy() {}

} // namespace game