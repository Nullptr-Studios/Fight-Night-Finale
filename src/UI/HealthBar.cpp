#include "HealthBar.hpp"

#include "Controller/CameraController.hpp"
#include "Objects/Camera.hpp"
namespace game {
void HealthBar::Update(double deltaTime) {
  UIProgressBar::Update(deltaTime);
  m_progress = static_cast<float>(m_currentHealth) /m_maxHealth;
}
}