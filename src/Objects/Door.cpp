//
// Created by cmgbp on 25/03/2025.
//

#include "Door.hpp"

void game::Door::Open() {
  std::cout<<"Door::Open"<<std::endl;
  m_isOpen = true;
  m_timer = 0.0f;
  //TODO: Animate it
}

void game::Door::Close() {
  std::cout<<"Door::Close"<<std::endl;
  m_isOpen = false;
  //TODO: Animate it
}

void game::Door::Update(double deltaTime) {
  if (!m_isOpen) {return;}
  m_timer += deltaTime;
  if (m_timer > m_timerMax) {
    Close();
  }
}