//
// Created by Xein on 4/9/2025.
//

#include "CasinoSign.hpp"

namespace game {
CasinoSign::CasinoSign(const Sigma::id_t id) : Actor(id) {
  m_animComp = new Sigma::Animation::AnimationComponent(this);
  auto animationAtlas = GET_ANIMATION->LoadTextureAtlas("assets/objects/CasinoSign.json");
  m_animComp->SetTextureAtlas(animationAtlas);
  m_animComp->SetLoop(true);
  m_animComp->SetCurrentAnim("casino-sign");
  m_animComp->PlayAnim();
}

glm::mat3 *CasinoSign::GetTextureTransform() {
  m_tMtx = m_animComp->GetTextureMatrix();
  return &m_tMtx;
}

} // game