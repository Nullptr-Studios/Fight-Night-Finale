#include "Boss.hpp"
#include "Random.hpp"
#include "aecore/imgui/imgui.h"


namespace game {

void Boss::DebugWindow() {
  ImGui::DragInt("Current State", &m_currentState);
  ImGui::DragInt("Next State", &m_nextState);
}
void Boss::Update(double delta) { 
  Enemy::Update(delta); 
  m_player = GetNearestPlayer();
}

void Boss::Init() {
  Enemy::Init();

  // Setup Animation
  auto anim = GET_ANIMATION->LoadTextureAtlas("assets/characters/Boss/anim-data.json");
  m_animComp->SetTextureAtlas(anim);
  m_animComp->SetCurrentAnim("Idle");
  SetTexture(anim->textureStr.c_str());
  m_animComp->PlayAnim();

  // Setup player collider
  m_collider->box.Set(25, 25, 50, 50, 10, transform.offset);
  m_collider->SetColliderType(Sigma::Collision::COLLISION);
  m_collider->SetColliderFlags(Sigma::Collision::ENEMY);
  m_collider->damage = 1.0f;
  m_collider->SetOwner(this);

  m_defaultState = STATE_IDLE;
  m_nextState = STATE_IDLE;
}

void Boss::Start() {
  Enemy::Start();
  BindState(STATE_GOTO, [this] { GotoState(); });
  BindState(STATE_BASIC, [this] { BasicAttack(); });
  BindState(STATE_SPECIAL, [this] { SpecialAttack(); });
  BindState(STATE_PURSUE, [this] { Pursue(); });
  BindState(STATE_RETREAT, [this] { Retreat(); });
}

void Boss::Transition() {
  m_jsonPath = "assets/characters/Boss/behaviourDose.json";
  Serialize();
}

void Boss::IdleState() {
  if (!m_isDoingSomething) return;
  m_nextState = STATE_BASIC;
  SetState(STATE_PURSUE);
}

void Boss::GotoState() {
  if (!m_isDoingSomething) return;
  glm::vec2 position = (glm::vec2) transform.GetDepthPosition();
  glm::vec2 direction = glm::normalize(m_goto - position);
  if ((direction.x >= 0) != (transform.relativeScale.x >= 0)) {
    transform.relativeScale.x *= -1;
  }
  if (!m_sceneBoundsPoly->IsPointInside((glm::vec2) transform.position + (direction * 5.0f)) || glm::distance(position, m_goto) < 1.0f) {
    WaitSeconds(.1f, m_nextState);
    return;
  }
  m_animComp->SetCurrentAnim("Walk");
  Move(direction);
}

void Boss::Pursue() { 
  if (!m_isDoingSomething) return;
  m_animComp->SetCurrentAnim("Idle");
  m_goto = (glm::vec2)m_player->transform.position + (Sigma::Random::Circle() * 30.0f);
  while (!m_sceneBoundsPoly->IsPointInside(m_goto)) {
    m_goto = (glm::vec2)m_player->transform.position + (Sigma::Random::Circle() * 30.0f);
  }
  WaitSeconds(.1f, STATE_GOTO);
}

void Boss::Retreat() { 
  if (!m_isDoingSomething) return;
  m_animComp->SetCurrentAnim("Idle");
  m_goto = (glm::vec2)m_player->transform.position + (Sigma::Random::Circle() * 150.0f);
  while (!m_sceneBoundsPoly->IsPointInside(m_goto)) {
    m_goto = (glm::vec2)m_player->transform.position + (Sigma::Random::Circle() * 150.0f);
  }
  WaitSeconds(.1f, STATE_GOTO);
}

void Boss::BasicAttack() {
  if (!m_isDoingSomething) return;
  glm::vec2 position = (glm::vec2) transform.GetDepthPosition();
  float distance = glm::distance(position, m_goto);
  if (distance < 5.0f) {
    BasicAttack();
    EndAttack();
    WaitSeconds(.1f, STATE_PURSUE);
  } else {
    WaitSeconds(.1f, STATE_PURSUE);
  }
}

void Boss::SpecialAttack() {
  if (!m_isDoingSomething) return;
  glm::vec2 position = (glm::vec2) transform.GetDepthPosition();
  float distance = glm::distance(position, m_goto);
  if (distance < 5.0f) {
    BasicAttack();
    EndAttack();
  } else {
    WaitSeconds(.1f, STATE_RETREAT);
  }
}

void Boss::EndAttack() {
  if (m_nextState == STATE_BASIC) {
    m_nextState = STATE_SPECIAL;
    WaitSeconds(.1f, STATE_RETREAT);
  } else {
    m_nextState = STATE_BASIC;
    WaitSeconds(.1f, STATE_PURSUE);
  }
}


} // namespace game
