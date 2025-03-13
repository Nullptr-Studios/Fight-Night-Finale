#include "BigEnemy.hpp"
#include "Random.hpp"
#include "Enemies/DefaultEnemy.hpp"
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

  m_defaultState = STATE_WANDER;
  m_defaultState = STATE_FOLLOW;
  targetLeft = rand()%2;
}

void BigEnemy::FollowState() {
  if (!m_isDoingSomething) return;

  if (m_nearest == nullptr)
    return;

  
  isAvoiding = false;
  m_animComp->SetCurrentAnim("Walk");
  glm::vec3 targets[2];
  targets[0] = m_nearest->transform.GetDepthPosition()+ glm::vec3(-50,0,0);
  targets[1] = m_nearest->transform.GetDepthPosition()+ glm::vec3(50,0,0);
  m_position = ((targetLeft)?targets[0]:targets[1]);

  if (fabs(m_distance.y) <= 25 && fabs(m_distance.x) <= 60 && fabs(m_distance.x) >= 30) {
    m_timer = Sigma::Random::Float(.2f, .3f);
    m_nextState = STATE_ATTACK;
    SetState(STATE_PAUSED);
  } else if (fabs(m_distance.y) <= 25 && fabs(m_distance.x) <= 60 && fabs(m_distance.x) <= 30) {
    m_nextState = STATE_FOLLOW;
    SetState(STATE_DISPERSE);
  } else {
    m_nextState = STATE_FOLLOW;
    m_timer = 2;
    SetState(STATE_GOTO);
  }
}

void BigEnemy::AttackState() {
  if (!m_isDoingSomething) return;
  isAvoiding = false;
  if ((m_distance.x >= 0) != (transform.relativeScale.x >= 0)) {
    transform.relativeScale.x *= -1;
  }
  if(rand()%3) {
    targetLeft = !targetLeft;
  } 
  BasicAttack();
}
}
