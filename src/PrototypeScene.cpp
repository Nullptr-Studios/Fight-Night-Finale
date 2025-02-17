#include "PrototypeScene.hpp"
#include "Controller/CameraController.hpp"
#include "Core.hpp"
#include "Enemies/Enemy.hpp"
#include "Factory.hpp"
#include "Objects/Actor.hpp"
#include "Objects/CameraFollow.hpp"
#include "UI/HealthBar.hpp"
#include "Objects/Debug/PunchingBag.hpp"
#include "Player/Player.hpp"

namespace game {

void PrototypeScene::Load() {
  GameScene::Load();
  std::cout << "PrototypeScene::Load()" << std::endl;

  GET_CAMERA->SetCurrentCamera(GET_FACTORY->CreateObject<Sigma::CameraFollow>("Main Camera"));
  GET_CAMERA->GetCurrentCamera()->size = 2;

  auto *floor = GET_FACTORY->CreateObject<Sigma::Actor>();
  floor->SetTexture("assets/prototype-scene-2/t-floor.png");
  floor->transform.scale = {1061.0f, 346.0f};
  floor->transform.position.z = -5000;

  auto *walls = GET_FACTORY->CreateObject<Sigma::Actor>();
  walls->SetTexture("assets/prototype-scene-2/t-walls.png");
  walls->transform.scale = {1061.0f, 346.0f};
  walls->transform.position.z = -5000;

  auto healthBar = GET_FACTORY->CreateObject<game::HealthBar>("Progress");
  healthBar->m_screenSpaceTransform.scale = {350, 10};
  healthBar->m_screenSpaceTransform.position = {0,550,0};
  healthBar->m_progress = 1;
  healthBar->SetTexture("assets/core/debug_red.png");
  
  auto p = GET_FACTORY->CreateObject<game::Player>("Player", -1, "assets/characters/player/behaviour.json");
  p->transform.position.x = m_playerStartPos.x;
  p->transform.position.y = m_playerStartPos.y;
  p->transform.position.z = 0.0f;
  p->m_healthBar = healthBar;


  auto s = GET_FACTORY->CreateObject<game::PunchingBag>("PunchingBag");
  s->transform.position.x = -278;
  s->transform.position.y = -10;
  s->transform.position.z = 10;

  m_players.push_back(p);

  dynamic_cast<Sigma::CameraFollow*>(GET_CAMERA->GetCurrentCamera())->m_targetP1 = p;
}
void PrototypeScene::Update(double delta) {
  GameScene::Update(delta);

  // If pressed key 2 create 2nd player
  if (AEInputGamepadButtonTriggered(0, 0x0010)) {
    // Check to avoid having infinite player 2 objects -x
    if (m_players.size() >= 2) return;

    auto healthBar2 = GET_FACTORY->CreateObject<game::HealthBar>("Progress");
    healthBar2->m_screenSpaceTransform.scale = {350, 10};
    healthBar2->m_screenSpaceTransform.position = {0, 530, 0};
    healthBar2->m_progress = 1;
    healthBar2->SetTexture("assets/core/debug_red.png");
    auto p2 = GET_FACTORY->CreateObject<game::Player>("Player2", 0, "assets/characters/player/behaviour.json");
    p2->transform.position.x = m_playerStartPos.x;
    p2->transform.position.y = m_playerStartPos.y;
    p2->transform.position.z = 0.0f;
    p2->m_healthBar = healthBar2;
    dynamic_cast<Sigma::CameraFollow*>(GET_CAMERA->GetCurrentCamera())->m_targetP2 = p2;
    m_players.push_back(p2);
  }

}

  
}
