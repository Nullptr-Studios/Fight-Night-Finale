//
// Created by cmgbp on 25/03/2025.
//
#pragma once
#include "Objects/Actor.hpp"

namespace game {
class Door : public Sigma::Actor {
  public:
    explicit Door(uint32_t id, float time) : Actor(id) {m_timerMax = time;}

  void Open();
  void Close();
  void Update(double deltaTime) override;

private:
  float m_timerMax;
  float m_timer = 0.0f;
  bool m_isOpen = false;

};

}
