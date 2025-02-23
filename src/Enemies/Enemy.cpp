#include "Enemy.hpp"
#include "aecore/AEFrameRateController.h"

#define DEBUG_ENEMY

namespace game {

void Enemy::Serialize() {
  Character::Serialize();
  m_attackDistance = j["distanceToAttack"];
}

void Enemy::Init() {
  Character::Init();

  transform.relativeScale = glm::vec2(1);

}

void Enemy::Start() {
  Character::Start();

  BindState(STATE_IDLE, std::bind(&Enemy::IdleState, this));
  BindState(STATE_WAIT, std::bind(&Enemy::TimerState, this));
  BindState(STATE_DEAD, std::bind(&Enemy::DeadState, this));

  SetState(STATE_IDLE);
}

void Enemy::OnDamage(const Sigma::Damage::DamageEvent& e) {
  if (e.GetOther()->GetName().contains("Enemy")) return;
 
  Character::OnDamage(e);
  if (!GetAlive()) SetState(STATE_DEAD);
}

void Enemy::Enable(std::array<Player*, 2>* players) {
  SetPlayers(players);
  if (!m_players->operator[](0)) {
    std::cout << "[Enemy] " << GetName() << ": Tried to enable without valid player reference\n";
    return;
  }

  m_enabled = true;
}

void Enemy::SetPlayers(std::array<Player*, 2>* players) { m_players = players; }

Player* Enemy::GetNearestPlayer() {
  if (!m_players->operator[](0) && !m_players->operator[](1)) return nullptr;
  if (!m_players->operator[](1)) return m_players->operator[](0);
  if (!m_players->operator[](0)) return m_players->operator[](1);

  // TODO: Find an actual way to do this
  try {
    float distance0 = glm::distance(transform.GetDepthPosition(), m_players->operator[](0)->transform.GetDepthPosition());
    float distance1 = glm::distance(transform.GetDepthPosition(), m_players->operator[](1)->transform.GetDepthPosition());

    if (distance0 >= distance1) return m_players->operator[](1);
    return m_players->operator[](0);

  } catch (const std::exception& e) {
    return nullptr;
  }
}

void Enemy::Update(double delta) {
  if (m_currentState == STATE_IDLE && m_enabled) {
    SetState(STATE_FOLLOW);
  } else if (!m_enabled && m_currentState != STATE_IDLE) {
    m_currentState == STATE_IDLE;
  }

  Character::Update(delta);

  if (!m_states[m_currentState]) {
    std::cout << "[Enemy] " << GetName() << ": The state you are trying to load is not binded\n";
    return;
  }

  // Calls the current state function
  m_states[m_currentState]();
}

void Enemy::SetState(int state) {
  // Sanity check
  if (m_states[state] == nullptr){
    std::cout << "[Enemy] State " << state << " is not set, perhaps you forgot to bind it?\n";
    return;
  }

  m_currentState = state;
  #ifdef DEBUG_ENEMY
  std::cout << "[Enemy] " << GetName() << ": Set current state to " << (int)state << "\n";
  #endif
}

void Enemy::BindState(int state, const std::function<void()>& function) {
  // Sanity check
  if (!function) return;

  m_states.insert({state, function});

  #ifdef DEBUG_ENEMY
  std::cout << "[Enemy] " << GetName() << ": Binded state " << (int)state << "\n";
  #endif
}

void Enemy::WaitSeconds(float time, int nextState) {
  m_timerSeconds = time;
  m_timerNextState = nextState;
  SetState(STATE_WAIT);
}

void Enemy::TimerState() {
  // Sanity check
  if (m_timerSeconds == -1.0f) {
    std::cout << "[Enemy] Timer state was not set up beforehand, state set to IDLE\n";
    SetState(STATE_IDLE);
    return;
  }

  if (m_animComp) m_animComp->SetCurrentAnim("Idle");
  m_timer += static_cast<float>(AEGetFrameTime());

  if (m_timer >= m_timerSeconds) {
    SetState(m_timerNextState);
    m_timerNextState = STATE_IDLE;
    m_timerSeconds = -1.0f;
    m_timer = 0.0f;
  }
}

}
