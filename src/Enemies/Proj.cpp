#include "Proj.hpp"
#include <memory>
#include "Collision/Collider.hpp"
#include "Collision/CollisionEvent.hpp"
#include "DamageSystem/DamageEvent.hpp"
#include "Player/Player.hpp"
namespace game {

void Proj::Init() {
  m_collider = std::make_unique<Sigma::Collision::BoxCollider>(Sigma::Collision::ColliderFlag::BULLET, Sigma::Collision::ColliderType::DAMAGE);
  m_collider->box.Set(glm::vec3{10, 10, 10});
  m_collider->SetOwner(this);
  m_collider->damage = m_damage;
  m_collider->knockback = {};
  transform.scale = {10,10};

}

void Proj::Update(double delta) {
  transform.position += velocity * static_cast<float>(delta);
}

bool Proj::OnCollision(Sigma::Collision::CollisionEvent &e) {
  GET_FACTORY->DestroyObject(this->GetId());
  return false;
}
} // namespace game
