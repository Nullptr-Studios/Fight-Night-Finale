#include "Player.hpp"

#include <UI/DeadMenu.hpp>

#include "Collision/Collider.hpp"
#include "Collision/CollisionEvent.hpp"
#include "Factory.hpp"
#include "GameManager.hpp"

#include "Audio/AudioEngine.hpp"

#include "UI/HealthBar.hpp"
#include "UI/MainMenu.hpp"
#include "core.hpp"

namespace game {

AEGfxFont* font;
void Player::Init() {
  Character::Init();

  m_deadScene = new MainMenu("DeadMenu", 0);
  
  transform.relativeScale = glm::vec2(1);

  // Setup Animation
  auto anim = GET_ANIMATION->LoadTextureAtlas("assets/characters/player/anim-data.json");
  m_animComp->SetTextureAtlas(anim);
  m_animComp->SetCurrentAnim("Idle");
  SetTexture(anim->textureStr.c_str());
  m_animComp->PlayAnim();

  // Setup Controller
  m_controllerComponent = std::make_unique<PlayerController>(this);
  m_controllerComponent->SetControllerID(m_controllerId);

  // setup player collider
  m_collider->box.Set(25, 25, 50, 50, 25, transform.offset);
  m_collider->SetColliderType(Sigma::Collision::COLLISION);
  m_collider->damage = 1.0f;
  m_collider->SetOwner(this);

}

void Player::Start() {
  Character::Start();

  m_healthBar->m_maxHealth = m_maxHealth;
  m_healthBar->m_currentHealth = GetHealth();
  
  // this is complete jankyness -d
  // m_debugPlayerCol = GET_FACTORY->CreateObject<Sigma::Actor>("Debug Attack");
}

void Player::Update(double delta) {
  Character::Update(delta);
  if (m_controllerComponent)
    m_controllerComponent->Update();
  
  if (GetIsIdle())
    if (velocity.x != 0 || velocity.y != 0) {
    m_animComp->SetCurrentAnim("Walk");
    }else {
    m_animComp->SetCurrentAnim("Idle");
    }

  // m_collider->DebugDraw(m_debugPlayerCol, this, "assets/core/debug_blue.png");

}

void Player::Destroy() {
  Character::Destroy();
  AEGfxFontFree(font);
}

void Player::OnDamage(const Sigma::Damage::DamageEvent &e)
{
  Character::OnDamage(e);

  std::cout << "Damage with " << e.GetOther()->GetName() << "\n";
  std::cout << GetHealth() << "\n";
  m_healthBar->m_currentHealth = GetHealth();

  if (!m_isAlive) {
    GET_MANAGER->LoadScene(m_deadScene);
    GET_MANAGER->UnloadScene(0u);
  }
}

} // namespace game
