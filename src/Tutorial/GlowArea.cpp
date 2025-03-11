#include "GlowArea.hpp"
#include "Collision/Collider.hpp"
#include "Collision/CollisionEvent.hpp"
#include "GameManager.hpp"
#include "Player/Player.hpp"
#include "Objects/Manager/GameplayManager.hpp"

namespace game {

void GlowArea::Init() {
  // TODO: Do glow animation
  SetTexture("assets/objects/area-static.png");
  transform.scale = {122, 46};

  m_collider = std::make_unique<Sigma::Collision::BoxCollider>(Sigma::Collision::PLAYER, Sigma::Collision::COLLISION);
  m_collider->box.Set({122, 46, 5});
}

bool GlowArea::OnCollision(Sigma::Collision::CollisionEvent& e) {
  auto players = GameplayManager::GetInstance()->GetPlayers();
  // FIXME: This might not work on release????
  if (players->operator[](1).player != nullptr) m_playerCount = 2;

  if (dynamic_cast<Player*>(e.GetOther()) == players->operator[](0).player) m_player1 = true;
  else if (dynamic_cast<Player*>(e.GetOther()) == players->operator[](1).player) m_player2 = true;

  if ((m_player1 && m_playerCount == 1) || (m_player1 && m_player2)) {
    GameplayManager::GetInstance()->GotoNextScene();
  }
  return true;
}

}

