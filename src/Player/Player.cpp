#include "Player.hpp"

#include "Audio/AudioEngine.hpp"


namespace game {
void Player::Init() {
  Character::Init();
  
  transform.relativeScale = glm::vec2(2);
  GET_AUDIO->LoadBank("assets/banks/Master.bank");
  GET_AUDIO->LoadBank("assets/banks/Master.strings.bank");
  GET_AUDIO->LoadBank("assets/banks/Music.bank");


}

void Player::Start() {
  Character::Start();
  
  auto anim = GET_ANIMATION->LoadTextureAtlas("assets/Test.json");
  m_animComp->SetTextureAtlas(anim);
  m_animComp->SetCurrentAnim("Idle");
  SetTexture(anim->textureStr.c_str());
  m_animComp->PlayAnim();
  
  m_controllerComponent = std::make_unique<PlayerController>(this);
  m_controllerComponent->SetControllerID(m_controllerId);
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

}

void Player::Destroy() { Character::Destroy(); }

} // namespace game