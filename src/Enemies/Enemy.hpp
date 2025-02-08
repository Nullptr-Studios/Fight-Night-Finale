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
    ATTACK,
    DEAD
  };

public:
  explicit Enemy(const Sigma::id_t id) : Character(id) {}

  void Init() override;
  void Start() override;
  void Update(double delta) override;
  void Destroy() override;

  void Serialize() override;

  bool OnCollision(Sigma::Collision::CollisionEvent& e) override;
  // bool OnDamage(Sigma::Damage::DamageEvent& e) override;

  void SetPlayer(Player* player) { m_player = player; }

protected:
  void SetState(EnemyState state) { m_state = state; }
  EnemyState GetState() { return m_state; }

private:
  Player* m_player = nullptr;

  EnemyState m_state = FOLLOW;
  void OnFollow(double delta);
  void OnAttack(double delta);
  void OnDead(double delta);

  float m_distanceToAttack = 0.0f;
  glm::vec3 m_distance = glm::vec3(0.0f);
};

}
