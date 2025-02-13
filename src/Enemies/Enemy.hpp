/**
 * @file Enemy.hpp
 * @author Xein
 * @date 07/02/25
 *
 * @brief [Brief description of the file's purpose]
 */
#pragma once
#include <pch.hpp>
#include "Collision/CollisionEvent.hpp"
#include "Objects/Character.hpp"

namespace game {
class Player;

class Enemy : public Sigma::Character {
  enum EnemyState {
    FOLLOW = 0,
    SEPARATE,
    ATTACK,
    DEAD
  };

public:
  explicit Enemy(const Sigma::id_t id, const std::string& jsonPath) : Character(id, jsonPath) {}

  void Init() override;
  void Start() override;
  void Update(double delta) override;
  void Destroy() override;

  void Serialize() override;

  bool OnCollision(Sigma::Collision::CollisionEvent& e) override;
  void OnDamage(const Sigma::Damage::DamageEvent& e) override;

  void SetPlayer(Player* player) { m_player = player; }

protected:
  void SetState(EnemyState state) { m_state = state; }
  EnemyState GetState() { return m_state; }

private:
  Player* m_player = nullptr;
  Actor* m_debugCol = nullptr;

  EnemyState m_state = FOLLOW;
  void OnFollow();
  void OnSeparate();
  void OnAttack();
  void OnDead();

  float m_distanceToAttack = 0.0f;
  glm::vec3 m_distance = glm::vec3(0.0f);
};

}
