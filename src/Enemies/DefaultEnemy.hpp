/**
 * @file DefaultEnemy.hpp
 * @author Xein
 * @date 21/02/25
 *
 * @brief [Brief description of the file's purpose]
 * TODO: follow states need to attack at better distance
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

  static constexpr int STATE_PAUSED = 9;     ///< @constexpr STATE_PAUSED      The enemy pauses for a while and switches states
  static constexpr int STATE_WALK = 10;     ///< @constexpr STATE_WALK         The enemy Walks for a bit
  static constexpr int STATE_GOTO = 11;     ///< @constexpr STATE_GOTO         The enemy GOTO's point
  static constexpr int STATE_REPOSING= 12;     ///< @constexpr STATE_GOTO         The enemy GOTO's point


protected:
  void OnFullComboPerformed(bool super = false) override;

  void EndedMove() override;

  virtual void WalkState();

  virtual void GoToState();
  virtual void FollowState();
  virtual void PausedState();
  virtual void DisperseState();
  virtual void AvoidState();
  virtual void RepositionState();
  virtual void RePosing();
  virtual void AttackState();
  
  void DeadState() override;


  void DebugWindow() override;

  Player* m_nearest{};
  glm::vec3 m_distance = glm::vec3(0.0f);
  glm::vec2 m_position = glm::vec2(0.0f);
  float detectionRange = 100;
  double m_timer{};
  int m_nextState= 0;
private:
// Idk if this should be private or protected yet -x
};

}
