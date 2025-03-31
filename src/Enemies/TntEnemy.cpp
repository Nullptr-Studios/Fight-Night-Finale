#include "TntEnemy.hpp"
#include "Random.hpp"
#include "Enemies/Tnt.hpp"
#include "glm/trigonometric.hpp"
#define GLM_ENABLE_EXPERIMENTAL
#include "glm/gtx/rotate_vector.hpp"

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
  glm::vec3 targets[2];

  targets[0] = m_nearest->transform.GetDepthPosition()+ glm::vec3(-200,0,0);
  targets[1] = m_nearest->transform.GetDepthPosition()+ glm::vec3(200,0,0);
  m_position = ((m_distance.x >= 0)?targets[0]:targets[1]);
  if (!m_sceneBoundsPoly->IsPointInside((glm::vec2) m_position)) {
    m_position = ((m_distance.x >= 0) ? targets[1] : targets[0]);
  }
  if (!m_sceneBoundsPoly->IsPointInside((glm::vec2) m_position)) {
    targets[0] = m_nearest->transform.GetDepthPosition() + glm::vec3(0, -200, 0);
    targets[1] = m_nearest->transform.GetDepthPosition() + glm::vec3(0, 200, 0);
    m_position = ((m_distance.x >= 0) ? targets[1] : targets[0]);
  }
  if (!m_sceneBoundsPoly->IsPointInside((glm::vec2) m_position)) {
    m_position = ((m_distance.x >= 0) ? targets[0] : targets[1]);
  }

  while(!m_sceneBoundsPoly->IsPointInside((glm::vec2) m_position)) {
    Sigma::Random::Circle();
    m_position = (glm::vec2)m_nearest->transform.position + (Sigma::Random::Circle() * 200.0f); //:3 dario faults
  }

  if (!m_sceneBoundsPoly->IsPointInside((glm::vec2) m_position)) {
    m_timer = 0.1;
    m_nextState = STATE_FOLLOW;
    SetState(STATE_PAUSED);
    return;
  }

  m_animComp->SetCurrentAnim("Walk");

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


