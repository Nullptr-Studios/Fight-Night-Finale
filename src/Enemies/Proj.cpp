#include "Proj.hpp"
#include <memory>

#include "Collision/Collider.hpp"
#include "Collision/CollisionEvent.hpp"
#include "DamageSystem/DamageEvent.hpp"
#include "GameManager.hpp"
#include "Player/Player.hpp"

#include "Random.hpp"
namespace game {

void Proj::Init() {
  m_collider = std::make_unique<Sigma::Collision::BoxCollider>(Sigma::Collision::ColliderFlag::BULLET, Sigma::Collision::ColliderType::DAMAGE);
  m_collider->box.Set(glm::vec3{5, 5, 5});
  m_collider->SetOwner(this);
  m_collider->damage = m_damage;
  m_collider->knockback = {200,10};
  transform.scale = {10,10};
  SetTexture("assets/objects/chip.png");
  auto e = GET_MANAGER->GetRandomEngine();
  std::uniform_real_distribution<> dist2(0.f, 1.f);
  glm::vec4 color = {dist2(*e), dist2(*e), dist2(*e), 1.0f};
  SetTint(color);
}

void Proj::Update(double delta) {
  transform.position += velocity * static_cast<float>(delta);
  m_timer += delta;
  if (m_timer >= 10) {
    GET_FACTORY->DestroyObject(this->GetId());
  }
}

bool Proj::OnCollision(Sigma::Collision::CollisionEvent &e) {
  GET_FACTORY->DestroyObject(this->GetId());
  return false;
}
} // namespace game
