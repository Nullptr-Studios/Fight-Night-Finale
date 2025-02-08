//
// Created by dariormt on 08/02/2025.
//

#include "PunchingBag.hpp"

namespace game {
void PunchingBag::Init() {
  Damageable::Init();

  m_animComp = std::make_unique<Sigma::Animation::AnimationComponent>(this);

  auto anim = GET_ANIMATION->LoadTextureAtlas("assets/PunchingBag.json");
  m_animComp->SetTextureAtlas(anim);
  m_animComp->SetCurrentAnim("Hit");
  m_animComp->PlayAnim();
  SetTexture(m_animComp->GetTextureAtlas()->textureStr.c_str());
  transform.relativeScale = glm::vec2(2);
}
void PunchingBag::Update(double delta) {
  Damageable::Update(delta);
  
  m_animComp->Update(delta);
}

glm::mat3 *PunchingBag::GetTextureTransform()
{
  auto mtx = m_animComp->GetTextureMatrix();
  m_tMtx = glm::FromAEX(mtx);
  return &m_tMtx;
}
} // namespace game
