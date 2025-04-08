/**
 * @file Boss.hpp
 * @author Dante Harper
 * @date 01/04/25
 *
 * @brief [TODO: Brief description of the file's purpose]
 */

#pragma once

#include "Enemies/Enemy.hpp"
#include "Enemies/Proj.hpp"
#include "UI/HealthBar.hpp"
#include "UI/UIImage.hpp"

namespace game {
class Boss : public Enemy {
public:
  Boss(const Sigma::id_t id, const char *jsonPath);
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

  void SpecialOne();
  void SpecialTwo();

  void Destroy() override;

  bool IsInBounds(glm::vec2 pos);
  void DebugWindow() override;
  void EndedMove() override;
  void FacePlayer();
  void OnFullComboPerformed(bool super) override;
  void Taunt();

  void OnDamage(const Sigma::Damage::DamageEvent &e) override;

private:
  float m_baseMaxSpeed;
  Player *m_player{};
  float m_timer{};
  bool m_phaseDose{};
  glm::vec2 m_goto{};
  int m_nextState{};
  int m_consectutiveAttack{};
  bool dash{};
  std::vector<std::shared_ptr<Proj>> destructionQueue;
  std::vector<std::shared_ptr<Enemy>> enemyDeletionQueue;

  void SpawnWave1();
  void SpawnWave2();
  void SpawnWave3();

  bool m_wave1 = false;
  bool m_wave2 = false;
  bool m_wave3 = false;

  // Boss UI
  std::shared_ptr<Sigma::UIImage> m_barBorder;
  std::shared_ptr<Sigma::UIImage> m_barBackground;
  std::shared_ptr<HealthBar> m_bar;
};

} // namespace game
