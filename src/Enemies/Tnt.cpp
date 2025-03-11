#include "Tnt.hpp"
#include "Core.hpp"
#include "Collision/OneHitCollider.hpp"
#include "Factory.hpp"
#include "Collision/Collider.hpp"
#include "aecore/imgui/imgui.h"
#include "Collision/OneHitCollider.hpp"
#include "DamageSystem/DamageEvent.hpp"
namespace game {

void Tnt::Init() {
  m_attackCollider = GET_FACTORY->CreateObject<Sigma::Collision::OneHitCollider>("Attack Collider");
  m_attackCollider->GetCollider()->enabled = false;
  m_boomBox = {100,100,100};
  m_powBox = {300,300};
  m_damage = 30;
}

void Tnt::Update(double delta) {
  if (boom) {
    return;
  }
  m_timer += (float)delta;
  if (m_timer >= 8) {
    boom = true;
    m_attackCollider->Do(transform.position, m_boomBox, m_damage, this, Sigma::Damage::DamageType::DAMAGE,m_powBox, true);
  }

}

void Tnt::DebugWindow() {
  Actor::DebugWindow();

  if (ImGui::CollapsingHeader("BOOM")) {
    if (ImGui::Button("Boom")) {
      m_attackCollider->Do(transform.position, m_boomBox, m_damage, this, Sigma::Damage::DamageType::DAMAGE,m_powBox, true);
    }
    if (ImGui::Button("Launch")) {
      m_attackCollider->Do(transform.position, m_boomBox, m_damage, this, Sigma::Damage::DamageType::DAMAGE,m_powBox, true);
    }
  }
}
void Tnt::Destroy() {
  if (m_attackCollider != nullptr)
    GET_FACTORY->DestroyObject(m_attackCollider);
}
}

