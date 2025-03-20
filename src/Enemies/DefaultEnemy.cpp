#include "DefaultEnemy.hpp"
#include <random>
#include "Factory.hpp"
#include "Polygon.hpp"
#include "Random.hpp"
#include "aecore/AEFrameRateController.h"
#include "aecore/imgui/imgui.h"
#include "glm/geometric.hpp"

namespace game {

void DefaultEnemy::DebugWindow() {
  Enemy::DebugWindow();
  if (ImGui::CollapsingHeader("Default Enemy")) {
    ImGui::DragFloat2("Distance", &m_distance.x);
    ImGui::DragFloat2("Random Pos", &m_position.x);
    ImGui::InputDouble("Timer", &m_timer);
    ImGui::Checkbox("IsAvoiding", &isAvoiding);
  }
}

void DefaultEnemy::Init() {
  Enemy::Init();

  // Setup Animation
  auto anim = GET_ANIMATION->LoadTextureAtlas("assets/characters/BasicEnemy/anim-data.json");
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

  m_defaultState = STATE_WANDER;
  m_defaultState = STATE_FOLLOW;
}

void DefaultEnemy::Start() {
  Enemy::Start();

  BindState(STATE_WALK, [this] { WalkState(); });
  BindState(STATE_PAUSED, [this] { PausedState(); });
  BindState(STATE_WANDER, [this] { WanderState(); });
  BindState(STATE_FOLLOW, [this] { FollowState(); });
  BindState(STATE_ATTACK, [this] { AttackState(); });
  BindState(STATE_DISPERSE, [this] { DisperseState(); });
  BindState(STATE_GOTO, [this] { GoToState(); });
  BindState(STATE_REPOSITION, [this] { RepositionState(); });
  BindState(STATE_REPOSING, [this] { RePosing(); });
  // BindState(STATE_AVOID, std::bind(&DefaultEnemy::AvoidState, this));
}

void DefaultEnemy::Update(double delta) {
  if (m_timer > 0) {
    m_timer -= delta;
  }
  m_nearest = GetNearestPlayer();
  if (!m_nearest) {
    m_timer = -1;
    SetState(STATE_IDLE);
  } else {
    m_distance = m_nearest->transform.GetDepthPosition() - transform.GetDepthPosition();
  }
  Enemy::Update(delta);
}

void DefaultEnemy::WalkState() {
  if (!m_isDoingSomething)
    return;
  if (m_timer <= 0) {
    m_position = {};
    m_timer = Sigma::Random::Float(.9f, 1.1f);
    SetState(STATE_PAUSED);
  }
  m_animComp->SetCurrentAnim("Walk");
  Move({m_position.x, m_position.y});
  if ((m_position.x >= 0) != (transform.relativeScale.x >= 0)) {
    transform.relativeScale.x *= -1;
  }
  if (!m_sceneBoundsPoly->IsPointInside((glm::vec2) transform.position + (m_position * 5.0f))) {
    m_timer = Sigma::Random::Float(.9f, 1.1f);
    SetState(STATE_PAUSED);
  }
}

void DefaultEnemy::PausedState() {
  if (!m_isDoingSomething)
    return;
  if (m_timer <= 0) {
    SetState(m_nextState);
  }
  m_animComp->SetCurrentAnim("Idle");
}

void DefaultEnemy::WanderState() {
  if (!m_isDoingSomething)
    return;
  isAvoiding = false;
  m_position = Sigma::Random::Circle();
  while (!m_sceneBoundsPoly->IsPointInside((glm::vec2) transform.position + (m_position * 5.0f))) {
    m_position = Sigma::Random::Circle();
  }
  m_position = Sigma::Random::Circle();
  m_timer = Sigma::Random::Float(.9f, 1.1f);
  m_nextState = STATE_WANDER;
  SetState(STATE_WALK);

  if (m_distance.length() <= detectionRange) {
    SetState(STATE_FOLLOW);
    m_defaultState = STATE_FOLLOW;
  }
}

void DefaultEnemy::FollowState() {
  if (!m_isDoingSomething)
    return;

  if (m_nearest == nullptr)
    return;

  isAvoiding = false;
  m_animComp->SetCurrentAnim("Walk");
  glm::vec3 targets[2];
  targets[0] = m_nearest->transform.GetDepthPosition() + glm::vec3(-50, 0, 0);
  targets[1] = m_nearest->transform.GetDepthPosition() + glm::vec3(50, 0, 0);
  m_position = ((m_distance.x >= 0) ? targets[0] : targets[1]);

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

void DefaultEnemy::AttackState() {
  if (!m_isDoingSomething)
    return;
  isAvoiding = false;
  if ((m_distance.x >= 0) != (transform.relativeScale.x >= 0)) {
    transform.relativeScale.x *= -1;
  }
  BasicAttack();
}

void DefaultEnemy::GoToState() {
  glm::vec2 position = (glm::vec2) transform.GetDepthPosition();
  glm::vec2 direction = glm::normalize(m_position - position);
  if ((direction.x >= 0) != (transform.relativeScale.x >= 0)) {
    transform.relativeScale.x *= -1;
  }
  if (!m_sceneBoundsPoly->IsPointInside((glm::vec2) transform.position + (direction * 5.0f)) ||
      glm::distance(position, m_position) < 1.0f || m_timer <= 0) {
    m_position = {};
    SetState(m_nextState);
    return;
  }
  Move(direction);
}

void DefaultEnemy::DisperseState() {
  if (!m_isDoingSomething)
    return;
  glm::vec2 position = (glm::vec2) transform.GetDepthPosition();
  std::random_device rd;
  std::mt19937 gen(rd());
  std::uniform_int_distribution<> distrib_x(30, 60);
  std::uniform_int_distribution<> distrib_y(-30, 30);
  m_position = m_nearest->transform.GetDepthPosition();

  if (m_position.x - position.x >= 0)
    m_position.x -= 60 + static_cast<float>(distrib_x(gen));
  else
    m_position.x += m_attackDistance - static_cast<float>(distrib_x(gen));
  m_position.y = (m_nearest->transform.GetDepthPosition().y + static_cast<float>(distrib_y(gen)));
  m_timer = 2;
  SetState(STATE_GOTO);
}

void DefaultEnemy::AvoidState() {
  // TODO: Implement this
}

void DefaultEnemy::RePosing() {
  m_animComp->SetCurrentAnim("Walk");

  glm::vec2 position = {transform.GetDepthPosition().x, transform.GetDepthPosition().y};
  Move(glm::normalize(m_position - position));
  if (glm::distance(position, m_position) < 1.0f || m_timer <= 0) {
    m_position = {0.0f, 0.0f};
    m_nextState = STATE_FOLLOW;
    WaitSeconds(0.5f, STATE_FOLLOW);
  }

  // Swaps the sprite if not facing the same way -x
  if ((glm::normalize(m_position - position).x >= 0) != (transform.relativeScale.x >= 0)) {
    transform.relativeScale.x *= -1;
  }
}

void DefaultEnemy::RepositionState() {
  if (!m_isDoingSomething)
    return;
  isAvoiding = false;
  glm::vec2 position = {transform.GetDepthPosition().x, transform.GetDepthPosition().y};
  Player *nearest = GetNearestPlayer();
  if (!nearest) {
    SetState(STATE_IDLE);
    return;
  }

  auto playerScale = nearest->transform.scale;
  auto playerPosition = nearest->transform.position;

  std::random_device rd;
  std::mt19937 gen(rd());
  std::uniform_int_distribution<> distrib_x(-playerScale.x * 2, playerScale.x * 2);
  std::uniform_int_distribution<> distrib_y(-playerScale.y, playerScale.y);

  m_position = {playerPosition.x + distrib_x(gen), playerPosition.y + distrib_y(gen)};

  if (m_sceneBoundsPoly->IsPointInside(m_position)) {
    m_timer = 2;
    SetState(STATE_REPOSING);
  }
}


void DefaultEnemy::DeadState() {
  // GET_FACTORY->DestroyObject(m_debugCol->GetId());
  // GET_FACTORY->DestroyObject(GetId());

  m_enabled = false;
}

void DefaultEnemy::OnFullComboPerformed() {
  m_timer = Sigma::Random::Float(1.2f, 1.6f);
  m_nextState = STATE_REPOSITION; // TODO: change this to reposition
  SetState(STATE_PAUSED);
}

void DefaultEnemy::EndedMove() {
  if (!m_hasDoneDamage) {
    OnFullComboPerformed();
  }
}

void DefaultEnemy::Destroy() { Enemy::Destroy(); }

} // namespace game
