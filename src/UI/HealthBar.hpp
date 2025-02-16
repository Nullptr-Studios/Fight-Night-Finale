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
  explicit HealthBar(Sigma::id_t id) : UIProgressBar(id) {}
  void Start() override;
  void Update(double deltaTime) override;
  int m_maxHealth{};
  int m_currentHealth{};

private:
  glm::vec2 m_screenPos{};
};
} // namespace game
