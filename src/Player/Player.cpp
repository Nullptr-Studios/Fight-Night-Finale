#include "Player.hpp"

namespace game {
void Player::Init() {
  Character::Init();
  
  transform.relativeScale = glm::vec2(3);
}

void Player::Start() {
  Character::Start();
  
  auto anim = GET_ANIMATION->LoadTextureAtlas("assets/TestAnimPlayer.json");
  m_animComp->SetTextureAtlas(anim);
  m_animComp->SetCurrentAnim("Idle");
  SetTexture("assets/TestAnimPlayer.png");
  m_animComp->PlayAnim();
  
  m_controllerComponent = std::make_unique<PlayerController>(this);
  m_controllerComponent->GetControllerID();
}

void Player::Update(double delta) {
  Character::Update(delta);
  if (m_controllerComponent)
    m_controllerComponent->Update();

  if (velocity.x != 0 || velocity.y != 0) {
    m_animComp->SetCurrentAnim("Walk");
  }else {
    m_animComp->SetCurrentAnim("Idle");
  }

  if (velocity.x < 0) {
    transform.relativeScale.x = -3;
  } else {
    transform.relativeScale.x = 3;
  }
}

void Player::Destroy() {}

} // namespace game