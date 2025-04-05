#include "Door.hpp"
#include <AnimationSystem/AnimationComponent.hpp>

void game::Door::Init() {
  Actor::Init();
  m_animComp = new Sigma::Animation::AnimationComponent(this);
  auto anim = GET_ANIMATION->LoadTextureAtlas("assets/objects/DoorsAtlas.json");
  m_animComp->SetOnAnimationEnd([this](const std::string& animName) { Door::animationEnded(animName); });
  m_animComp->SetTextureAtlas(anim);
  m_animComp->SetCurrentAnim("Idle"+std::to_string(m_doorType));
  SetTexture(anim->textureStr.c_str());
  m_animComp->PlayAndStop();
}

void game::Door::Open(float timeToClose, bool forever) {
  m_timer = 0.0f;
  m_timerMax = timeToClose;
  if (!m_isOpen) {
    m_animComp->SetCurrentAnim("Open"+std::to_string(m_doorType));
    m_animComp->PlayAndStop();
    if (!forever)
      m_isOpen = true;
  }
}

void game::Door::Close() {
  m_animComp->SetCurrentAnim("Close"+std::to_string(m_doorType));
  m_animComp->PlayAndStop();
}

void game::Door::Update(double deltaTime) {
  Sigma::Actor::Update(deltaTime);
  if (m_isOpen) {
    m_timer += deltaTime;
    if (m_timer > m_timerMax)
      Close();
  }
}

glm::mat3 *game::Door::GetTextureTransform() {
  m_tMtx = m_animComp->GetTextureMatrix();
  return &m_tMtx;
}

void game::Door::animationEnded(const std::string& animName) {
 if (animName == "Close"+std::to_string(m_doorType)) {
   m_isOpen = false;
 }
}

void game::Door::LateUpdate(double deltaTime) {
  Sigma::Actor::LateUpdate(deltaTime);
  if (m_animComp)
    m_animComp->Update(deltaTime);
}