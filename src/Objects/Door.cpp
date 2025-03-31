#include "Door.hpp"

void game::Door::Init() {
  Actor::Init();
  auto anim = GET_ANIMATION->LoadTextureAtlas("assets/objects/DoorsAtlas.json");
  m_animComp->SetTextureAtlas(anim);
  m_animComp->SetCurrentAnim("Idle"+std::to_string(m_doorType));
  SetTexture(anim->textureStr.c_str());
  m_animComp->PlayAndStop();
}

void game::Door::Open() {
  m_timer = 0.0f;
  if (!m_isOpen) {
    m_animComp->SetCurrentAnim("Open"+std::to_string(m_doorType));
    m_animComp->PlayAndStop();
    std::cout<<"Door::Open"<<std::endl;
  }
  m_isOpen = true;
  m_isIdle = false;
}

void game::Door::Close() {
  std::cout<<"Door::Close"<<std::endl;
  m_isOpen = false;
  m_isIdle = true;
  m_animComp->SetCurrentAnim("Close"+std::to_string(m_doorType));
  m_animComp->PlayAndStop();
}

void game::Door::Update(double deltaTime) {
  if (!m_isOpen && m_isIdle) {
    m_animComp->SetCurrentAnim("Idle"+std::to_string(m_doorType));
    m_animComp->PlayAndStop();
    return;
  }
  m_timer += deltaTime;
  if (m_timer > m_timerMax) { Close(); }
}