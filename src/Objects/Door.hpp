
#pragma once
#include "Objects/Actor.hpp"

namespace game {
/**
 * @brief class for a door object with open/close capabilities.
 */
class Door : public Sigma::Actor {
  public:
    explicit Door(uint32_t id, int doorType) : Actor(id) { m_doorType = glm::clamp(1, doorType, 4); }

  void Init() override;
  void Open(float timeToClose = 1.5f, bool forever = false);
  void Close();
  void Update(double deltaTime) override;
  void LateUpdate(double deltaTime) override;

  void animationEnded(const std::string& animName);

  glm::mat3 *GetTextureTransform() override;

//private:
  float m_timerMax = 1.5f;
  float m_timer = 0.0f;
  int m_doorType = 1;
  bool m_isOpen = false;
};
}