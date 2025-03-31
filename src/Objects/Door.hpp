
#pragma once
#include "Objects/Actor.hpp"

namespace game {
/**
 * @brief class for a door object with open/close capabilities.
 */
class Door : public Sigma::Actor {
  public:
    explicit Door(uint32_t id, int doorType) : Actor(id) { m_doorType = glm::clamp(1, doorType, 3); }

  void Init() override;
  void Open();
  void Close();
  void Update(double deltaTime) override;

private:
  float m_timerMax = 1.5f;
  float m_timer = 0.0f;
  int m_doorType = 1;
  bool m_isOpen = false;
  bool m_isIdle = true;
};
}