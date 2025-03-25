#include "TntEnemy.hpp"
#include "Random.hpp"
#include "Enemies/Tnt.hpp"

namespace game {
void TntEnemy::Init() {
  Enemy::Init();
  // Setup Animation
  auto anim = GET_ANIMATION->LoadTextureAtlas("assets/characters/tntEnemy/anim-data.json");
  m_animComp->SetTextureAtlas(anim);
  m_animComp->SetCurrentAnim("Idle");
  SetTexture(anim->textureStr.c_str());
  m_animComp->PlayAnim();

  // Setup player collider
  m_collider->box.Set(25, 25, 50, 50, 25, transform.offset);
  m_collider->SetColliderType(Sigma::Collision::COLLISION);
  m_collider->damage = 1.0f;
  m_collider->SetOwner(this);

  m_defaultState = STATE_FOLLOW;
}

void TntEnemy::FollowState() {
  if (!m_isDoingSomething) return;
  isAvoiding = false;
  m_animComp->SetCurrentAnim("Walk");
  glm::vec3 targets[2];
  targets[0] = m_nearest->transform.GetDepthPosition()+ glm::vec3(-200,0,0);
  targets[1] = m_nearest->transform.GetDepthPosition()+ glm::vec3(200,0,0);
  m_position = ((m_distance.x >= 0)?targets[0]:targets[1]);

  if (fabs(m_distance.y) <= 200 && fabs(m_distance.x) <= 200 && fabs(m_distance.x) >= 150) {
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

void TntEnemy::AttackState() {
  if (!m_isDoingSomething) return;
  isAvoiding = false;
  if ((m_distance.x >= 0) != (transform.relativeScale.x >= 0)) {
    transform.relativeScale.x *= -1;
  }

  auto tnt = GET_FACTORY->CreateObject<Tnt>("Tnt");
  tnt->m_start = transform.position;
  tnt->m_target = m_nearest->transform.position;
  BasicAttack();
}
}


