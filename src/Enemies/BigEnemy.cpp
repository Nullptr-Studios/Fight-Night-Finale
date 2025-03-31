#include "BigEnemy.hpp"
#include "Enemies/Enemy.hpp"

namespace game {

void BigEnemy::Init() {
  Enemy::Init();
  m_attackCollider = GET_FACTORY->CreateObject<Sigma::Collision::OneHitCollider>("Attack Collider");
  // Setup Animation
  auto anim = GET_ANIMATION->LoadTextureAtlas("assets/characters/bigEnemy/anim-data.json");
  m_animComp->SetTextureAtlas(anim);
  m_animComp->SetCurrentAnim("Idle");
  SetTexture(anim->textureStr.c_str());
  m_animComp->PlayAnim();

  // Setup player collider
  m_collider->box.Set(25, 25, 50, 50, 25, transform.offset);
  m_collider->SetColliderType(Sigma::Collision::COLLISION);
  m_collider->SetColliderFlags(Sigma::Collision::ENEMY);
  m_collider->damage = 1.0f;
  m_collider->SetOwner(this);

  m_defaultState = STATE_FOLLOW;
  targetLeft = rand() % 2;
}

void BigEnemy::AttackState() {
  if (!m_isDoingSomething)
    return;
  isAvoiding = false;
  if ((m_distance.x >= 0) != (transform.relativeScale.x >= 0)) {
    transform.relativeScale.x *= -1;
  }
  if (rand() % 3) {
    targetLeft = !targetLeft;
  }
  TakeKnockback({0, 600});
  // BasicAttack();
  attack = true;
  m_nextState = STATE_FOLLOW;
  m_timer = 2;
  SetState(STATE_PAUSED);
}

void BigEnemy::LandedOnGround() {
  transform.position.y = m_movementYFloor;
  velocity.y = 0;
  isInAir = false;

  m_invincible = true;
  m_isRecovering = true;
  if (attack) {
    m_attackCollider->Do(transform.position + (glm::vec3){0,0,0}, {150,50,100}, 13, this, Sigma::Damage::DAMAGE,{100,140},true);
    attack = false;
  }
  if (GetAlive())
    m_animComp->SetCurrentAnim("Recover");
  else {
    m_animComp->SetCurrentAnim("Recover");
    m_animComp->GotoFrame(0);
    m_animComp->StopAnim();
  }
}
} // namespace game
