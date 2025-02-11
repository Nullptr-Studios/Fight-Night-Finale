#include "Player.hpp"
#include "Collision/Collider.hpp"
#include "Collision/CollisionEvent.hpp"

#include "Audio/AudioEngine.hpp"


namespace game {
void Player::Init() {
  Character::Init();
  
  transform.relativeScale = glm::vec2(1);
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

  m_collider = std::make_unique<Sigma::Collision::BoxCollider>(Sigma::Collision::PLAYER, Sigma::Collision::COLLISION);
  m_collider->box.Set(50, 50, 50, 50);
  m_collider->damage = 1.0f;
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

  m_attackCollider->DebugDraw(this, AE_COLORS_RED);

}

void Player::Destroy() { Character::Destroy(); }

void Player::OnDamage(const Sigma::Damage::DamageEvent &e)
{
  Damageable::OnDamage(e);
  std::cout << "Damage with " << e.GetOther()->GetName() << "\n";
  std::cout << GetHealth() << "\n";
}

} // namespace game
