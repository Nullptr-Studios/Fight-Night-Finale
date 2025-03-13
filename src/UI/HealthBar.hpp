/**
 * @file HealthBar.hpp
 * @author dante
 * @date 2/16/2025
 *
 * @brief Health Bar
 */
#pragma once
#include "UI/UIProgressBar.hpp"
namespace game {
class HealthBar final : public Sigma::UIProgressBar {
public:
  explicit HealthBar(Sigma::id_t id, std::string sprite) : UIProgressBar(id, std::move(sprite)) {}
  void Update(double deltaTime) override;
  float m_maxHealth = 1.0f; ///<@brief Maximum Health
  float m_currentHealth = 1.0f; ///<@brief Current Health

  void DebugWindow() override;

};
} // namespace game
