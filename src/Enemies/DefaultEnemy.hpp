/**
 * @file DefaultEnemy.hpp
 * @author Xein
 * @date 21/02/25
 *
 * @brief [Brief description of the file's purpose]
 */
#pragma once
#include "Enemies/Enemy.hpp"

namespace game {

class DefaultEnemy : public Enemy {
public:
  DefaultEnemy(const Sigma::id_t id, const char* jsonPath) : Enemy(id, jsonPath) {}

protected:
  void Start() override;

  virtual void FollowState();
  virtual void DisperseState();
  virtual void AvoidState();
  virtual void RepositionState();
  virtual void AttackState();
  virtual void DeadState();

  float m_attackDistance = 0.0f;

private:
// Idk if this should be private or protected yet -x
  glm::vec3 m_distance = glm::vec3(0.0f);
  glm::vec2 m_randomPosition = glm::vec2(0.0f);
  bool m_isIdle = false;
};

}
