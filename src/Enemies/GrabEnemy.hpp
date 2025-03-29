/**
 * @file GrabEnemy.hpp
 * @author Dante Harper
 * @date 25/03/25
 *
 * @brief [TODO: Brief description of the file's purpose]
 */

#pragma once
#include "Enemies/DefaultEnemy.hpp"

namespace game {
class GrabEnemy : public DefaultEnemy {
private:
  bool targetLeft{};
public:
  GrabEnemy(const Sigma::id_t id, const char* jsonPath) : DefaultEnemy(id, jsonPath) {}
  void Init() override;
  void Start() override;
  void FollowState() override;
  void AttackState() override;
  void Update(double delta) override;

  void GrabAttackState();

  static constexpr int STATE_GRABATTACK = 13;     ///< @constexpr STATE_GOTO         The enemy GOTO's point

  float cooldown = 0;
};
}
