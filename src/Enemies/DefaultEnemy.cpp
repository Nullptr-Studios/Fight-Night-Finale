#include "DefaultEnemy.hpp"
#include <ostream>
#include <random>
#include "Polygon.hpp"
#include "Factory.hpp"
#include "Random.hpp"
#include "aecore/imgui/imgui.h"

namespace game {

void DefaultEnemy::DebugWindow() {
  Enemy::DebugWindow();
  if (ImGui::CollapsingHeader("Default Enemy")) {
    ImGui::DragFloat2("Distance", &m_distance.x);
    ImGui::DragFloat2("Random Pos", &m_position.x);
    ImGui::InputDouble("Timer", &m_timer);

  }
}

void DefaultEnemy::Init() {
  Enemy::Init();

  // Setup Animation
  auto anim = GET_ANIMATION->LoadTextureAtlas("assets/characters/enemy/anim-data.json");
  m_animComp->SetTextureAtlas(anim);
  m_animComp->SetCurrentAnim("Idle");
  SetTexture(anim->textureStr.c_str());
  m_animComp->PlayAnim();

  // Setup player collider
  m_collider->box.Set(25, 25, 50, 50, 25, transform.offset);
  m_collider->SetColliderType(Sigma::Collision::COLLISION);
  m_collider->damage = 1.0f;
  m_collider->SetOwner(this);

  m_defaultState = STATE_WANDER;
  m_defaultState = STATE_FOLLOW;
}

void DefaultEnemy::Start() {
  Enemy::Start();

  BindState(STATE_WALK, std::bind(&DefaultEnemy::WalkState, this));
  BindState(STATE_PAUSED, std::bind(&DefaultEnemy::PausedState, this));
  BindState(STATE_WANDER, std::bind(&DefaultEnemy::WanderState, this));
  BindState(STATE_FOLLOW, std::bind(&DefaultEnemy::FollowState, this));
  BindState(STATE_ATTACK, std::bind(&DefaultEnemy::AttackState, this));
  BindState(STATE_DISPERSE, std::bind(&DefaultEnemy::DisperseState, this));
  BindState(STATE_GOTO, std::bind(&DefaultEnemy::GoToState, this));
  // BindState(STATE_AVOID, std::bind(&DefaultEnemy::AvoidState, this));
  // BindState(STATE_REPOSITION, std::bind(&DefaultEnemy::RepositionState, this));
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
  if (!m_isDoingSomething) return;
  if (m_timer <= 0) {
    m_position = {};
    m_timer = Sigma::Random::Float(.9f, 1.1f);
    m_nextState = STATE_WANDER;
    SetState(STATE_PAUSED);
  }
  m_animComp->SetCurrentAnim("Walk");
  Move( {m_position.x, m_position.y} );
  if ((m_position.x >= 0) != (transform.relativeScale.x >= 0)) {
    transform.relativeScale.x *= -1;
  }
  if (!m_sceneBoundsPoly->IsPointInside((glm::vec2)transform.position + (m_position * 5.0f))) {
    m_timer = Sigma::Random::Float(.9f, 1.1f);
    m_nextState = STATE_WANDER;
    SetState(STATE_PAUSED);
  }

}

void DefaultEnemy::PausedState() {
  if (!m_isDoingSomething) return;
  if (m_timer <= 0) {
    SetState(m_nextState);
  }
  m_animComp->SetCurrentAnim("Idle");
}

void DefaultEnemy::WanderState() {
  if (!m_isDoingSomething) return;
  m_position = Sigma::Random::Circle();
  while (!m_sceneBoundsPoly->IsPointInside((glm::vec2)transform.position + (m_position * 5.0f))) {
    m_position = Sigma::Random::Circle();
  }
  m_timer = Sigma::Random::Float(.9f, 1.1f);
  SetState(STATE_WALK);
}

void DefaultEnemy::FollowState() {
  if (!m_isDoingSomething) return;
  m_animComp->SetCurrentAnim("Walk");
  glm::vec3 targets[2];
  targets[0] = m_nearest->transform.GetDepthPosition()+ glm::vec3(-50,0,0);
  targets[1] = m_nearest->transform.GetDepthPosition()+ glm::vec3(50,0,0);
  glm::vec3 direction = ((m_distance.x <= 0)?targets[0]:targets[1]) - transform.GetDepthPosition();
  Move({direction.x, direction.y });
  if ((direction.x >= 0) != (transform.relativeScale.x >= 0)) {
    transform.relativeScale.x *= -1;
  }

  if (fabs(m_distance.y) <= 25 && fabs(m_distance.x) <= 60 && fabs(m_distance.x) >= 30) {
    m_timer = Sigma::Random::Float(.2f, .3f);
    m_nextState = STATE_ATTACK;
    SetState(STATE_PAUSED);
  } else if (fabs(m_distance.y) <= 25 && fabs(m_distance.x) <= 60 && fabs(m_distance.x) <= 30) {
    SetState(STATE_DISPERSE);

  }
}

void DefaultEnemy::AttackState() {
  if (!m_isDoingSomething) return;
  BasicAttack();
}

void DefaultEnemy::GoToState() {
  m_animComp->SetCurrentAnim("Walk");
  glm::vec2 position = (glm::vec2)transform.GetDepthPosition();
  glm::vec2 direction = glm::normalize(m_position - position);
  if (!m_sceneBoundsPoly->IsPointInside((glm::vec2)transform.position + (direction * 5.0f)) || glm::distance(position, m_position) < 1.0f ) {
    m_position = {};
    SetState(m_nextState);
    return;
  }
  Move(direction);
}

void DefaultEnemy::DisperseState() {
  if (!m_isDoingSomething) return;
  glm::vec2 position = (glm::vec2)transform.GetDepthPosition();
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> distrib_x( 15, 30);
    std::uniform_int_distribution<> distrib_y(-30, 30);
    m_position = m_nearest->transform.GetDepthPosition();

    if (m_position.x - position.x >= 0) m_position.x -= 60 + static_cast<float>(distrib_x(gen));
    else                                m_position.x += m_attackDistance - static_cast<float>(distrib_x(gen));
    m_position.y = (m_nearest->transform.GetDepthPosition().y + static_cast<float>(distrib_y(gen)));
    m_nextState = STATE_FOLLOW;
    SetState(STATE_GOTO);
}

void DefaultEnemy::AvoidState() {
  // TODO: Implement this
}

void DefaultEnemy::RepositionState() {
  if (!m_isDoingSomething) return;
  // glm::vec2 position = {transform.GetDepthPosition().x, transform.GetDepthPosition().y};
  // m_animComp->SetCurrentAnim("Walk");
  //
  // if (m_randomPosition.x == 0.0f && m_randomPosition.y == 0.0f) {
  //   Player* nearest = GetNearestPlayer();
  //   if (!nearest) {
  //     SetState(STATE_IDLE);
  //     return;
  //   }
  //
  //   auto playerScale = nearest->transform.scale;
  //   auto pl enayerPosition = nearest->transform.position;
  //
  //   std::random_device rd;
  //   std::mt19937 gen(rd());
  //   std::uniform_int_distribution<> distrib_x(-playerScale.x * 2, playerScale.x * 2);
  //   std::uniform_int_distribution<> distrib_y(-playerScale.y, playerScale.y);
  //
  //   m_randomPosition = { playerPosition.x + distrib_x(gen), playerPosition.y + distrib_y(gen) };
  //
  //   // Avoid SEPARATE state if point is out of bounds -x
  //   if (!m_sceneBoundsPoly->IsPointInside(m_randomPosition)) {
  //     m_randomPosition = {0.0f, 0.0f};
  //     RepositionState();
  //     return;
  //   }
  // }
  //
  // Move(glm::normalize(m_randomPosition - position));
  // if (glm::distance(position, m_randomPosition) < 1.0f) {
  //   m_randomPosition = {0.0f, 0.0f};
  //   WaitSeconds(0.5f, STATE_FOLLOW);
  // }
  //
  // // Swaps the sprite if not facing the same way -x
  // if ((glm::normalize(m_randomPosition - position).x >= 0) != (transform.relativeScale.x >= 0)) {
  //   transform.relativeScale.x *= -1;
  // }
}


void DefaultEnemy::DeadState() {
  // GET_FACTORY->DestroyObject(m_debugCol->GetId());
  GET_FACTORY->DestroyObject(GetId());
}

void DefaultEnemy::OnFullComboPerformed() {
  m_timer = Sigma::Random::Float(1.2f,1.6f);
  m_nextState = STATE_FOLLOW;
  SetState(STATE_PAUSED);
}

void DefaultEnemy::Destroy() {
  Enemy::Destroy();
}

}
