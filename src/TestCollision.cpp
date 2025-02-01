#include "TestCollision.hpp"
#include "Collision/Collider.hpp"

namespace game {

void TestCollision::Start() {
  m_collider = std::make_unique<sigma::Collision::BoxCollider>(sigma::Collision::PLAYER, sigma::Collision::COLLISION);
  m_collider->box.Set(50, 50, 50, 50);

  transform.position = {200, 0, 0};
}

}
