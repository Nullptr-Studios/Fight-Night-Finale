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
  explicit HealthBar(Sigma::id_t id, std::string sprite) : UIProgressBar(id, sprite) {}
  void Update(double deltaTime) override;
  int m_maxHealth{}; ///<@brief Maximum Health
  int m_currentHealth{}; ///<@brief Current Health
};
} // namespace game
