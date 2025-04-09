#include "Tnt.hpp"
#include "Core.hpp"
#include "Collision/OneHitCollider.hpp"
#include "Factory.hpp"
#include "Collision/Collider.hpp"
#include "Polygon.hpp"
#include "aecore/imgui/imgui.h"
#include "Collision/OneHitCollider.hpp"
#include "DamageSystem/DamageEvent.hpp"
#include "glm/ext/quaternion_geometric.hpp"
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/compatibility.hpp>
namespace game {


void Tnt::Init() {
  m_attackCollider = GET_FACTORY->CreateObject<Sigma::Collision::OneHitCollider>("Attack Collider");
  m_attackCollider->GetCollider()->enabled = false;
  transform.scale = {12,12};
  SetTexture("assets/objects/tnt.png");
  m_boomBox = {100,100,100};
  m_powBox = {300,300};
  m_damage = 10;
  m_length = 1;
  m_timer = 0;

  m_hitEffect = GET_FACTORY->CreateObject<Sigma::EffectObject>("Hit Effect", "assets/objects/EffectsAtlas.json");
  m_hitEffect->transform.relativeScale = {1.5f, 1.5f};
}

void Tnt::Update(double delta) {
  m_timer += (float)delta;
  m_length = glm::length(m_start - m_target) /200.0f;
  if ( m_timer >= m_length + .5f) {
    GET_FACTORY->DestroyObject(this->GetId());
  }
  if (boom) {
    return;
  }
  if (m_timer >= m_length + .4) {
    boom = true;
    int id = GetId();
    m_attackCollider->Do(transform.position, m_boomBox, m_damage, this, Sigma::Damage::DamageType::DAMAGE,m_powBox, false);
    m_hitEffect->transform.position = transform.position+glm::vec3(0,0,1000);
    m_hitEffect->DoEffect("Explosion");
    transform.position = m_target;
  }
  if (m_timer <= m_length) {
    float t = m_timer / m_length;
    transform.position = glm::lerp(m_start,m_target,t);
  }
  transform.position.z = 0;
}

void Tnt::DebugWindow() {
  Actor::DebugWindow();

  if (ImGui::CollapsingHeader("BOOM")) {
    ImGui::DragFloat("m_timer", &m_timer);
    ImGui::DragFloat("m_length", &m_length);
    ImGui::DragFloat3("m_start", &m_start.x);
    ImGui::DragFloat3("m_target", &m_target.x);
    if (ImGui::Button("Boom")) {
      m_attackCollider->Do(transform.position, m_boomBox, m_damage, this, Sigma::Damage::DamageType::DAMAGE,m_powBox, true);
    }
    if (ImGui::Button("Launch")) {
      m_timer = 0;
      boom = false;
      transform.position = m_start;
    }
  }
}
void Tnt::Destroy() {
  if (m_attackCollider != nullptr)
    GET_FACTORY->DestroyObject(m_attackCollider);
}
}

#undef GLM_USE_EXPERIMENTAL
