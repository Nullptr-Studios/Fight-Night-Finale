/**
 * @file TntEnemy.hpp
 * @author Dante Harper
 * @date 11/03/25
 *
 * @brief BOOM BOOM HA HAH A HA HA HA HA HA
 */
#pragma once

#include "Enemies/DefaultEnemy.hpp"
namespace game {
class Tnt;
}
namespace game {
class TntEnemy : public DefaultEnemy {
public:
  TntEnemy(const Sigma::id_t id, const char* jsonPath) : DefaultEnemy(id, jsonPath) {}
  void Init() override;
  void FollowState() override;
  void AttackState() override;
  void Update(double delta) override;

  void Destroy() override;

private:
  std::shared_ptr<Tnt> m_tnt = nullptr;
  float m_cooldown = 0;

};
}

