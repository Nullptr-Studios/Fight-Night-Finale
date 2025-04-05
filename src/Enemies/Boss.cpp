#include "Boss.hpp"
#include "AnimationSystem/AnimationSystem.hpp"
#include "Core.hpp"
#include "Enemies/Proj.hpp"
#include "Factory.hpp"
#include "Random.hpp"
#include "aecore/imgui/imgui.h"
#include "glm/fwd.hpp"
#include "glm/geometric.hpp"


namespace game {

void Boss::DebugWindow() {
  Enemy::DebugWindow();
  ImGui::DragInt("Current State", &m_currentState);
  ImGui::DragInt("Next State", &m_nextState);
}
void Boss::Update(double delta) {
  Enemy::Update(delta);
  m_player = GetNearestPlayer();
  if (!m_phaseDose && m_isGrabbed) {
    float health = m_health;
    Transition();
    m_health = health;
  }
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
  BindState(STATE_BASIC, [this] { BasicState(); });
  BindState(STATE_SPECIAL, [this] { SpecialState(); });
  BindState(STATE_PURSUE, [this] { Pursue(); });
  BindState(STATE_RETREAT, [this] { Retreat(); });
}

void Boss::Transition() {
  auto anim = GET_ANIMATION->LoadTextureAtlas("assets/characters/Boss/anim-dataDose.json");
  m_animComp->SetTextureAtlas(anim);
  // m_animComp->SetCurrentAnim("Idle");
  SetTexture(anim->textureStr.c_str());
  m_animComp->PlayAnim();
  m_phaseDose = true;
}

bool Boss::IsInBounds(glm::vec2 pos) {
  return m_sceneBoundsPoly->IsPointInside(pos);
}

void Boss::IdleState() {
  if (!m_isDoingSomething)
    return;
  m_nextState = STATE_BASIC;
  SetState(STATE_PURSUE);
}

void Boss::GotoState() {
  if (!m_isDoingSomething)
    return;
  glm::vec2 position = (glm::vec2) transform.GetDepthPosition();
  glm::vec2 direction = glm::normalize(m_goto - position);
  if ((direction.x >= 0) != (transform.relativeScale.x >= 0)) {
    transform.relativeScale.x *= -1;
  }
  if (!IsInBounds((glm::vec2)transform.position + (direction * 5.0f)) ||
      glm::distance(position, m_goto) < 1.0f) {
    WaitSeconds(.1f, m_nextState);
    return;
  }
  m_animComp->SetCurrentAnim("Walk");
  Move(direction);
  if (dash) {
    Dash();
    dash = false;
  }
}

void Boss::Pursue() {
  if (!m_isDoingSomething) return;
  m_animComp->SetCurrentAnim("Idle");

  do {
    m_goto = (glm::vec2) m_player->transform.position + (Sigma::Random::Circle() * 30.0f);
  } while (!IsInBounds(m_goto));

  WaitSeconds(.1f, STATE_GOTO);
}

void Boss::Retreat() {
  if (!m_isDoingSomething) return;
  m_consectutiveAttack = 0;
  m_animComp->SetCurrentAnim("Idle");

  do {
    m_goto = (glm::vec2) m_player->transform.position + (Sigma::Random::Circle() * 150.0f);
  } while (!IsInBounds(m_goto));

  dash = true;
  WaitSeconds(.1f, STATE_GOTO);
}

void Boss::BasicState() {
  if (!m_isDoingSomething) return;
  glm::vec3 targets[2];
  targets[0] = m_player->transform.position + glm::vec3(-30, 0, 0);
  targets[1] = m_player->transform.position + glm::vec3(30, 0, 0);
  m_goto = glm::distance(transform.position, targets[0]) < glm::distance(transform.position, targets[1]) ? targets[0] : targets[1];
  glm::vec2 position = (glm::vec2) transform.GetDepthPosition();
  float distance = glm::distance(position, m_goto);
  if (distance <= 10) {
    FacePlayer();
    BasicAttack();
  } else {
    WaitSeconds(.1f, STATE_GOTO);
  }
}

void Boss::SpecialState() {
  if (!m_isDoingSomething) return;
  glm::vec2 position = (glm::vec2) transform.GetDepthPosition();
  float distance = glm::distance(position, m_goto);
  if (distance <= 10) {
    dash = false;
    FacePlayer();
    SpecialOne();
    if (m_consectutiveAttack >= 3) {
      m_consectutiveAttack = 0;
      EndedMove();
    }
  } else {
    WaitSeconds(.1f, STATE_RETREAT);
  }
}

void Boss::SpecialOne() {
  SuperAttack();
  m_consectutiveAttack++;
  std::shared_ptr<Proj> proj = GET_FACTORY->CreateObject<game::Proj>("Proj");
  proj->transform.position = transform.position + glm::vec3(0, 60, 0);
  proj->velocity =
    glm::normalize(proj->transform.position - (m_player->transform.position + glm::vec3(0, 55, 0))) * -200.0f;
  destructionQueue.push_back(proj);
}

void Boss::FacePlayer() {
  glm::vec3 distance = m_player->transform.GetDepthPosition() - transform.GetDepthPosition();
  if ((distance.x >= 0) != (transform.relativeScale.x >= 0)) {
    transform.relativeScale.x *= -1;
  }
}

void Boss::EndedMove() {
  if (m_hasDoneDamage && m_nextState == STATE_BASIC) {
    return;
  }
  if (rand() % 2 == 0) {
    m_nextState = STATE_SPECIAL;
    SetState(STATE_RETREAT);
  } else {
    m_nextState = STATE_BASIC;
    SetState(STATE_PURSUE);
  }
}

void Boss::Destroy() {
  Enemy::Destroy();
  while (!destructionQueue.empty()) {
    if (destructionQueue.back()) {
      GET_FACTORY->DestroyObject(destructionQueue.back());
    }
    destructionQueue.pop_back();
  }
}

} // namespace game
