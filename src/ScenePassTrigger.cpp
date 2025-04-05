#include "ScenePassTrigger.hpp"

#include "Player/Player.hpp"

namespace game {
void ScenePassTrigger::Init() {
  Object::Init();
  
  m_collider = std::make_unique<Sigma::Collision::BoxCollider>(Sigma::Collision::PLAYER, Sigma::Collision::COLLISION);
  m_collider->box.Set({6, 6, 5});
}

bool ScenePassTrigger::OnCollision(Sigma::Collision::CollisionEvent& e) {
  auto p = dynamic_cast<Player*>(e.GetOther());
  if(p){
    GameplayManager::GetInstance()->GotoNextScene();
    SetActive(false);
  }
  return true;
}
}

