/**
 * @file BigEnemy.hpp
 * @author Dante Harper
 * @date 10/03/25
 *
 * @brief i hate my life
 */
#pragma once

#include "Enemies/DefaultEnemy.hpp"
namespace game {
class BigEnemy : public DefaultEnemy {
private:
  bool targetLeft;
public:
  BigEnemy(const Sigma::id_t id, const char* jsonPath) : DefaultEnemy(id, jsonPath) {}
  void Init() override;
  void FollowState() override;
  void AttackState() override;

};
}
