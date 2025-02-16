/**
 * @file Enemy.hpp
 * @author Xein
 * @date 07/02/25
 *
 * @brief [Brief description of the file's purpose]
 */
#pragma once
#include <iterator>
#include <pch.hpp>
#include "Collision/CollisionEvent.hpp"
#include "Objects/Character.hpp"

namespace game {
class Player;

class Enemy : public Sigma::Character {
  enum EnemyState {
    IDLE = -1,
    FOLLOW = 0,
    WAIT,
    SEPARATE,
    RANDOM_SPARCE,
    ATTACK,
    DEAD
  };

public:
  explicit Enemy(const Sigma::id_t id, const std::string& jsonPath) : Character(id, jsonPath) {}

  void Init() override;
  void Serialize() override;
  void Start() override;
  void Update(double delta) override;
  void Destroy() override;

  bool OnCollision(Sigma::Collision::CollisionEvent& e) override;
  void OnDamage(const Sigma::Damage::DamageEvent& e) override;
  void OnFullComboPerformed() override;

  /**
   * @brief Tell the enemy to turn on its AI
   * @param players Array of the current active players
   */
  void Enable(std::array<Player*, 2> players);

protected:
  void SetState(EnemyState state) { m_state = state; }
  EnemyState GetState() { return m_state; }

private:
  Player* m_player = nullptr;
  Actor* m_debugCol = nullptr;

  EnemyState m_state = IDLE;
  void OnWait(double delta);
  void OnFollow();
  void OnSeparate();
  // TODO: I hate this name but I can't find anything better pls help me -x
  void OnRandomSparce();
  void OnAttack();
  void OnDead();

  /**
   * @brief Sets the timer to wait for an amount of seconds
   * @param time Time to wait in seconds
   * @param nextState Next state to switch when the timer finishes
   */
  inline void SetWait(float time, EnemyState nextState = FOLLOW) {
    if (nextState == IDLE) std::cout << "[Enemy] WARNING: Timer set to idle\n";

    m_timerSeconds = time;
    m_timerNextState = nextState;
    m_state = WAIT;
  }

  float m_timer = 0;
  float m_timerSeconds = 0;
  EnemyState m_timerNextState = IDLE;

  float m_distanceToAttack = 0.0f;
  glm::vec3 m_distance = glm::vec3(0.0f);
  glm::vec2 m_separateDirection = glm::vec2(0.0f);
};

}
