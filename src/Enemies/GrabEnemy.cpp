#include "GrabEnemy.hpp"
#include "Enemies/DefaultEnemy.hpp"
#include "Random.hpp"
#include "glm/geometric.hpp"


namespace game {

void GrabEnemy::Update(double delta) {
  DefaultEnemy::Update(delta);
  cooldown -= delta;
}

void GrabEnemy::Init() {
  Enemy::Init();
  // Setup Animation
  auto anim = GET_ANIMATION->LoadTextureAtlas("assets/characters/grabEnemy/anim-data.json");
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

void GrabEnemy::Start() {
  DefaultEnemy::Start();
  BindState(STATE_GRABATTACK, [this] { GrabAttackState(); });
}

void GrabEnemy::FollowState() {
  if (!m_isDoingSomething)
    return;

  if (m_nearest == nullptr)
    return;

  isAvoiding = false;
  m_animComp->SetCurrentAnim("Walk");
  glm::vec3 targets[2];
  targets[0] = m_nearest->transform.GetDepthPosition() + glm::vec3(0, -50, 0);
  targets[1] = m_nearest->transform.GetDepthPosition() + glm::vec3(0, 50, 0);
  m_position = ((targetLeft) ? targets[0] : targets[1]);

  if (!m_sceneBoundsPoly->IsPointInside((glm::vec2) m_position)) {
    m_position = ((targetLeft) ? targets[1] : targets[0]);
  }

  if (!m_sceneBoundsPoly->IsPointInside((glm::vec2) m_position)) {
    targets[0] = m_nearest->transform.GetDepthPosition() + glm::vec3(0, -25, 0);
    targets[1] = m_nearest->transform.GetDepthPosition() + glm::vec3(0, 25, 0);
    m_position = ((targetLeft) ? targets[0] : targets[1]);
  }

  if (!m_sceneBoundsPoly->IsPointInside((glm::vec2) m_position)) 
    m_position = ((targetLeft) ? targets[1] : targets[0]);

  if (fabs(m_distance.y) <= 60 && fabs(m_distance.x) <= 10) {
    m_timer = Sigma::Random::Float(.1f, .2f);
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

void GrabEnemy::AttackState() {
  if (!m_isDoingSomething)
    return;
  isAvoiding = false;
  if ((m_distance.x >= 0) != (transform.relativeScale.x >= 0)) {
    transform.relativeScale.x *= -1;
  }
  if (cooldown > 0) {
    m_timer = .1;
    m_nextState = STATE_FOLLOW;
    SetState(STATE_PAUSED);
    return;
  }
  m_nextState = STATE_FOLLOW;
  SetState(STATE_GRABATTACK);
  cooldown = 5;
}

void GrabEnemy::GrabAttackState() {
  if (glm::length(transform.position - m_nearest->transform.position) < 10) {
    BasicAttack();
    SetState(m_nextState);
    return;
  }
  m_position = m_nearest->transform.position;
  m_nextState = STATE_GRABATTACK;
  m_timer = 2;
  SetState(STATE_GOTO);
}
} // namespace game
