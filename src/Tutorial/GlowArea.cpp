#include "GlowArea.hpp"
#include "Collision/Collider.hpp"
#include "Collision/CollisionEvent.hpp"
#include "GameManager.hpp"
#include "Player/Player.hpp"
#include "Objects/Manager/GameplayManager.hpp"

namespace game {

void GlowArea::Init() {

  m_animComp = new Sigma::Animation::AnimationComponent(this);
  auto t = GET_ANIMATION->LoadTextureAtlas("assets/objects/GlowArea_Anim.json");
  m_animComp->SetTextureAtlas(t);
  SetTexture(t->textureStr.c_str());
  m_animComp->SetCurrentAnim("GlowArea");
  m_animComp->PlayAnim();

  transform.scale = {122, 46};

  m_collider = std::make_unique<Sigma::Collision::BoxCollider>(Sigma::Collision::PLAYER, Sigma::Collision::COLLISION);
  m_collider->box.Set({6, 6, 5});
}
void GlowArea::Update(double deltaTime) {
  Actor::Update(deltaTime);

  m_animComp->Update(deltaTime);

}

bool GlowArea::OnCollision(Sigma::Collision::CollisionEvent& e) {
  auto players = GameplayManager::GetInstance()->GetPlayers();
  // FIXME: This might not work on release????
  if (players->operator[](1).player != nullptr) m_playerCount = 2;

  if (dynamic_cast<Player*>(e.GetOther()) == players->operator[](0).player) m_player1 = true;
  else if (dynamic_cast<Player*>(e.GetOther()) == players->operator[](1).player) m_player2 = true;

  if ((m_player1 && m_playerCount == 1) || (m_player1 && m_player2)) {
    if (!m_doFuckingOnce) {
      GameplayManager::GetInstance()->GotoNextScene();
      m_doFuckingOnce = true;
      return false;
    }
  }
  return true;
}

}

