#include "TestCollision.hpp"
#include "Collision/Collider.hpp"

namespace game {

void TestCollision::Start() {
  m_collider = std::make_unique<Sigma::Collision::BoxCollider>(Sigma::Collision::PLAYER, Sigma::Collision::DAMAGE);
  m_collider->box.Set(50, 50, 50, 50, 50);

  transform.position = {200, 0, 0};
}

void TestCollision::OnDamage(const Sigma::Damage::DamageEvent &e) {
  Character::OnDamage(e);
  std::cout << "Object \"" << GetName() << "\" was damaged by \"" << e.GetOther()->GetName() << "\"\n";
  std::cout << "Current health: " << GetHealth() << "\n";
}

} // namespace game
