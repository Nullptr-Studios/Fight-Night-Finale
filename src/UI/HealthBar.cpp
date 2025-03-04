#include "HealthBar.hpp"
#include "aecore/imgui/imgui.h"

namespace game {
void HealthBar::Update(double deltaTime) {
  UIProgressBar::Update(deltaTime);
  m_progress = std::clamp(m_currentHealth / m_maxHealth, 0.0f, 1.0f);
}

void HealthBar::DebugWindow() {
  UIProgressBar::DebugWindow();

  if (ImGui::CollapsingHeader("Health Bar")) {
    ImGui::Value("Progress", m_progress);
    ImGui::DragFloat("Current Health", &m_currentHealth);
    ImGui::DragFloat("Maximum Health", &m_maxHealth);
  }
}

}
