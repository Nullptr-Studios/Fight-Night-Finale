#include "BigEnemy.hpp"
#include "Enemies/Enemy.hpp"

namespace game {

void BigEnemy::Init() {
  Enemy::Init();
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
  BasicAttack();
  
}
} // namespace game
