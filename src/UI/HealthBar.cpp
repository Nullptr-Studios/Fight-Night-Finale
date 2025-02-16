#include "HealthBar.hpp"

#include "Controller/CameraController.hpp"
#include "Objects/Camera.hpp"
namespace game {
void HealthBar::Start() {
  UIProgressBar::Start();
  m_screenPos = transform.position;
}
void HealthBar::Update(double deltaTime) {
  UIProgressBar::Update(deltaTime);
  transform.position = GET_CAMERA->GetCurrentCamera()->transform.position + glm::vec3(m_screenPos.x,m_screenPos.y,0);
  m_progress = (float)m_currentHealth/m_maxHealth;
}
}