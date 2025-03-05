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
  void Init() override;
  void Start() override;
  void Update(double delta) override;
  void Destroy() override;

protected:
  void OnFullComboPerformed() override;

  virtual void FollowState();
  virtual void DisperseState();
  virtual void AvoidState();
  virtual void RepositionState();
  virtual void AttackState();
  void DeadState() override;

private:
// Idk if this should be private or protected yet -x
  glm::vec3 m_distance = glm::vec3(0.0f);
  glm::vec2 m_randomPosition = glm::vec2(0.0f);
};

}
