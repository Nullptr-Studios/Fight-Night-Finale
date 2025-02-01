#include "TestCollision.hpp"
#include "Collision/Collider.hpp"

namespace game {

void TestCollision::Start() {
  m_collider = std::make_unique<Sigma::Collision::BoxCollider>(Sigma::Collision::PLAYER, Sigma::Collision::COLLISION);
  m_collider->box.Set(50, 50, 50, 50);

  transform.position = {200, 0, 0};
}

}
