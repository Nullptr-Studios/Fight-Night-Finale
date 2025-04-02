/**
 * @file Boss.hpp
 * @author Dante Harper
 * @date 01/04/25
 *
 * @brief [TODO: Brief description of the file's purpose]
 */

#pragma once

#include "Enemies/Enemy.hpp"
namespace game {
class Boss : public Enemy {
public:
  Boss(const Sigma::id_t id, const char *jsonPath) : Enemy(id, jsonPath) {}
  void Update(double delta) override;
  void Init() override;
  void Start() override;

  void Transition();

  static constexpr int STATE_PURSUE = 69;
  virtual void Pursue();
  static constexpr int STATE_RETREAT = 420;
  virtual void Retreat();

  static constexpr int STATE_GOTO = 11;
  virtual void GotoState();
  void IdleState() override;

  static constexpr int STATE_BASIC = 42;
  virtual void BasicState();

  static constexpr int STATE_SPECIAL = 96;
  virtual void SpecialState();

  void DebugWindow() override;
  void EndAttack();

private:
  Player* m_player{};
  float m_timer{};
  glm::vec2 m_goto{};
  int m_nextState{};

};
}
