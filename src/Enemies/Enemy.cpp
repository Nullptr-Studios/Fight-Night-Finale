#include "Enemy.hpp"

#include "Objects/Manager/GameplayManager.hpp"
#include "aecore/AEFrameRateController.h"
#include "aecore/imgui/imgui.h"

// #define DEBUG_ENEMY

namespace game {

void Enemy::Serialize() {
  Character::Serialize();
  m_attackDistance = j["distanceToAttack"];
  m_xp = j["experience"];
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

  if(m_invincible)
    return;

  int money = m_xp*(e.GetDamageAmount()/m_maxHealth);
  GameplayManager::GetInstance()->GiveXP(money);

  if (!GetAlive()) {
    SetState(STATE_DEAD);
    m_collider->enabled = false;
  }
}

void Enemy::DeadAnimFinish() {
  // GET_FACTORY->DestroyObject(m_debugCol->GetId());
  GET_FACTORY->DestroyObject(GetId());
}

void Enemy::Enable(std::array<PlayerStruct, 2>* players) {
  SetPlayers(players);
  /*if (!m_players[0].player && !m_players[1].player) {
    std::cout << "[Enemy] " << GetName() << ": Tried to enable without valid player reference\n";
    return;
  }*/

  m_enabled = true;
}

void Enemy::SetPlayers(std::array<PlayerStruct, 2>* players) { m_players = players; }

Player* Enemy::GetNearestPlayer() {
  if (!m_players->operator[](0).player && !m_players->operator[](1).player) return nullptr;
  if (!m_players->operator[](1).player) return m_players->operator[](0).player;
  if (!m_players->operator[](0).player) return m_players->operator[](1).player;

  float distance0 = glm::distance(transform.GetDepthPosition(), m_players->operator[](0).player->transform.GetDepthPosition());
  float distance1 = glm::distance(transform.GetDepthPosition(), m_players->operator[](1).player->transform.GetDepthPosition());

  if (distance0 >= distance1){
    if(m_players->operator[](1).player->GetAlive())
      return m_players->operator[](1).player;
  }
  if(m_players->operator[](0).player->GetAlive())
    return m_players->operator[](0).player;

  // if all checks fail return nullptr
  return nullptr;
}

void Enemy::Update(double delta) {


  if (m_currentState == STATE_IDLE && m_enabled) {
    SetState(m_defaultState);
  } else if (!m_enabled && m_currentState != STATE_IDLE) {
    m_currentState = STATE_IDLE;
  }

  Character::Update(delta);

  // Do not tick enemy logic if its inm air or recovering
  if(isInAir || m_isRecovering || !m_isDoingSomething)
    return;

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
  // if (m_states.find(state) != m_states.end()) { m_states[state] = nullptr; }
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

void Enemy::DebugWindow() {
  Character::DebugWindow();
  if (ImGui::CollapsingHeader("Enemy")) {
    const char *states[] = {"idle","follow","wait","dead","dispearse","avoid","reposition","attack","wander", "paused","walk","goto","reposing"};
    int selection = m_currentState;
    if (ImGui::Combo("Current State", &selection, states, 13)) {
      m_currentState = selection;
    }
    selection = m_defaultState;
    if (ImGui::Combo("Default State", &selection, states, 13)) {
      m_defaultState = selection;
    }
    ImGui::DragFloat("Attack Range", &m_attackDistance);
    ImGui::Checkbox("Enabled", &m_enabled);
  }
}

}
