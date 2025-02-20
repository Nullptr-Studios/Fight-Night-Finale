#include "Enemy.hpp"
#include "aecore/AEFrameRateController.h"

namespace game {

void Enemy::Start() {
  BindState(STATE_IDLE, std::bind(&Enemy::IdleState, this));
  BindState(STATE_WAIT, std::bind(&Enemy::TimerState, this));
}

void Enemy::Update(double delta) {
  // Calls the current state function
  m_states[m_currentState]();
}

void Enemy::SetState(char state) { 
  // Sanity check
  if (m_states[state] == nullptr){
    std::cout << "State " << state << " is not set, perhaps you forgot to bind it?\n";
    return;
  }

  m_currentState = state;
}

void Enemy::BindState(char state, const std::function<void()>& function) {
  // Sanity check
  if (!function) return;

  m_states[state] = function; 
}

void Enemy::WaitSeconds(float time, char nextState) {
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

  m_timer += static_cast<float>(AEGetFrameTime());

  if (m_timer >= m_timerSeconds) {
    SetState(m_timerNextState);
    m_timerNextState = STATE_IDLE;
    m_timerSeconds = -1.0f;
    m_timer = 0.0f;
  }
}

}
