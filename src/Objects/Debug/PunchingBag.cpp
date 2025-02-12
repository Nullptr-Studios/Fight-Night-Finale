//
// Created by dariormt on 08/02/2025.
//

#include "PunchingBag.hpp"

#include "Factory.hpp"

namespace game {
void PunchingBag::Init() {
  Damageable::Init();

  m_animComp = std::make_unique<Sigma::Animation::AnimationComponent>(this);

  auto anim = GET_ANIMATION->LoadTextureAtlas("assets/PunchingBag.json");
  m_animComp->SetTextureAtlas(anim);
  m_animComp->SetCurrentAnim("Hit");
  m_animComp->PlayAndStop();
  SetTexture(m_animComp->GetTextureAtlas()->textureStr.c_str());
  transform.relativeScale = glm::vec2(.75f);

  m_collider->box.Set(50,50,50,50,50, transform.offset);
  m_collider->SetColliderFlags(Sigma::Collision::ColliderFlag::ENEMY);

  m_debugCol = GET_FACTORY->CreateObject<Sigma::Actor>("Debug Col Punching Bag");

}
void PunchingBag::Update(double delta) {
  Damageable::Update(delta);

  m_animComp->Update(delta);
  m_collider->DebugDraw(m_debugCol, this, "assets/core/debug_red.png");
}
void PunchingBag::OnDamage(const Sigma::Damage::DamageEvent &e) {
  Damageable::OnDamage(e);
  std::cout << "Punching Bag was damaged by " << e.GetOther()->GetName() << "\n";
  m_animComp->PlayAndStop();
}

glm::mat3 *PunchingBag::GetTextureTransform()
{
  auto mtx = m_animComp->GetTextureMatrix();
  m_tMtx = glm::FromAEX(mtx);
  return &m_tMtx;
}
} // namespace game
