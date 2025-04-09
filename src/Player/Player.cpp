#include "Player.hpp"

#include <UI/DeadMenu.hpp>

#include "Collision/Collider.hpp"
#include "Effects/EffectObject.hpp"
#include "Enemies/BigEnemy.hpp"
#include "GameManager.hpp"
#include "Objects/Character.hpp"

namespace game {

AEGfxFont *font;
void Player::Init() {
  Character::Init();

  transform.relativeScale = glm::vec2(1);

  // Setup Animation
  auto anim = GET_ANIMATION->LoadTextureAtlas(m_isSecondPlayer ? "assets/characters/player/Player1.json" : "assets/characters/player/Player2.json");
  m_animComp->SetTextureAtlas(anim);
  m_animComp->SetCurrentAnim("Idle");
  SetTexture(anim->textureStr.c_str());
  m_animComp->PlayAnim();


  m_animComp->SetupTrailEffect(4, .07f, .5f, glm::vec4(1, 1, 1, .75f), glm::vec4(1, 1, 1, 0));

  // Setup Controller
  m_controllerComponent = std::make_unique<PlayerController>(this);
  m_controllerComponent->SetControllerID(m_controllerId);

  // setup player collider
  m_collider->box.Set(20, 20, 50, 50, 10, transform.offset);
  m_collider->SetColliderType(Sigma::Collision::COLLISION);
  m_collider->SetColliderFlags(Sigma::Collision::PLAYER | Sigma::Collision::BULLET);
  m_collider->damage = 1.0f;
  m_collider->SetOwner(this);
}
void Player::Serialize() {
  Character::Serialize();

}

void Player::Start() {
  Character::Start();

  // this is complete jankyness -d
  // m_debugPlayerCol = GET_FACTORY->CreateObject<Sigma::Actor>("Debug Attack");
}

void Player::Update(double delta) {
  Character::Update(delta);
  if (m_controllerComponent)
    m_controllerComponent->Update();

  if (GetIsIdle() && !m_inCombo) {
    if (velocity.x > .1f || velocity.x < -.1f || velocity.y > .1f || velocity.y < -.1f) {
      m_animComp->SetCurrentAnim("Walk");
    } else {
      m_animComp->SetCurrentAnim("Idle");
    }
  }

  // m_collider->DebugDraw(m_debugPlayerCol, this, "assets/core/debug_blue.png");
}
void Player::LateUpdate(double deltaTime) {
  Character::LateUpdate(deltaTime);

  if (!m_sceneBoundsPoly->IsPointInside(transform.position)) {
    GameplayManager::GetInstance()->RespawnPlayer(this);
  }
}

void Player::Destroy() {
  Character::Destroy();
  // AEGfxFontFree(font);
}
void Player::Respawn() {
  Character::Respawn();
  m_healthRecover = GetHealth();
  if (healthBar)
    healthBar->Update(GetHealth(), m_healthRecover);
}
void Player::DeadAnimFinish() {
  Character::DeadAnimFinish();
  transform.position.x += FLT_MAX;
  GameplayManager::GetInstance()->SetPlayerAsDead(this);
}

void Player::SuperAttackEnd() {
  m_health -= 10;

  if (healthBar)
    healthBar->Update(GetHealth<int>(), m_healthRecover);
}
void Player::DoSuperAttack() {
  /*m_health -= 10;

  if (healthBar)
    healthBar->Update(GetHealth<int>(), m_healthRecover);*/
}

void Player::RegainHPCombo() {

  if (m_health < m_healthRecover)
    m_health += 10;
}

void Player::OnDamage(const Sigma::Damage::DamageEvent &e) {
  Character::OnDamage(e);

  if (m_invincible)
    return;

  if (e.GetOther() != this)
    m_healthRecover = m_health;

  if (healthBar)
  {
    healthBar->Update(GetHealth<int>(), m_healthRecover);
    if(e.GetOther() != this)
      healthBar->ComboBreak();
  }
  if (!GetAlive())
    return;


  if (e.GetOther() != this) {
    m_controllerComponent->PlayerDamagedFeedback();
  } else {
    printf("hi dario\n");
  }


  if (dynamic_cast<BigEnemy*>(e.GetOther())) {
    // m_gotHitByFatEnemy = true;
  }
  // if (!m_isAlive && doFuckingOnce) {
  //   auto scene = dynamic_cast<PrototypeScene*>(GET_SCENE(0));
  //   if (!scene) return;
  //   if (GetId() == scene->m_players[0]->GetId()) scene->m_players[0] = nullptr;
  //   else if (GetId() == scene->m_players[1]->GetId()) scene->m_players[1] = nullptr;
  //
  //   // TODO: We need to check if the two players are dead
  //   //GET_MANAGER->LoadScene(m_deadScene);
  //   //GET_MANAGER->UnloadScene(0u);
  //   doFuckingOnce = false;
  // }
}

void Player::OnDoneDamage() {
  Character::OnDoneDamage();
  m_controllerComponent->PlayerAttackFeedback();

  // Combo counter
  
    healthBar->StreakAdd();
}

void Player::SetControllerID(int id) {
  m_controllerId = id;
  m_controllerComponent->SetControllerID(id);
}


void Player::LandedOnGround() {
  transform.position.y = m_movementYFloor;
  velocity.y = 0;
  isInAir = false;

  if (!m_gotHitByFatEnemy) {
    m_invincible = true;
  } else {
    m_gotHitByFatEnemy = false;
  }
  m_isRecovering = true;
  if (GetAlive())
    m_animComp->SetCurrentAnim("Recover");
  else {
    m_animComp->SetCurrentAnim("Recover");
    m_animComp->GotoFrame(0);
    m_animComp->StopAnim();
  }
}

} // namespace game
