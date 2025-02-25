#include "PrototypeScene.hpp"
#include "Controller/CameraController.hpp"
#include "Core.hpp"
#include "Enemies/DefaultEnemy.hpp"
#include "Enemies/Enemy.hpp"
#include "Factory.hpp"
#include "GameManager.hpp"
#include "Objects/Actor.hpp"
#include "Objects/CameraFollow.hpp"
#include "Objects/Debug/PunchingBag.hpp"
#include "Player/Player.hpp"
#include "UI/HealthBar.hpp"
#include "UI/MainMenu.hpp"
#include "core.hpp"

// #define DEBUG_CAMERA

namespace game {

void PrototypeScene::Load() {
  GameScene::Load();
  std::cout << "PrototypeScene::Load()" << std::endl;

  m_deadScene = new MainMenu("DeadMenu", 0);

#ifdef DEBUG_CAMERA
  GET_CAMERA->SetCurrentCamera(GET_FACTORY->CreateObject<Sigma::Camera>("Debug Camera"));
  GET_CAMERA->GetCurrentCamera()->size = 1;
#else
  GET_CAMERA->SetCurrentCamera(GET_FACTORY->CreateObject<Sigma::CameraFollow>("Main Camera"));
  GET_CAMERA->GetCurrentCamera()->size = 2;
#endif

  AddChild(GET_CAMERA->GetCurrentCamera());


  floor = GET_FACTORY->CreateObject<Sigma::Actor>();
  floor->SetTexture("assets/prototype-scene-2/t-floor.png");
  floor->transform.scale = {1061.0f, 346.0f};
  floor->transform.position.z = -5000;
  AddChild(floor);

  walls = GET_FACTORY->CreateObject<Sigma::Actor>();
  walls->SetTexture("assets/prototype-scene-2/t-walls.png");
  walls->transform.scale = {1061.0f, 346.0f};
  walls->transform.position.z = -5000;
  AddChild(walls);


  healthBar = GET_FACTORY->CreateObject<game::HealthBar>("Progress");
  healthBar->m_screenSpaceTransform.scale = {300, 20};
  healthBar->m_screenSpaceTransform.position = {0,450,0};
  healthBar->m_progress = 1;
  healthBar->SetTexture("assets/core/debug_red.png");
  AddChild(healthBar);


  p = GET_FACTORY->CreateObject<game::Player>("Player", -1, "assets/characters/player/behaviour.json");
  p->transform.position.x = m_playerStartPos.x;
  p->transform.position.y = m_playerStartPos.y;
  p->transform.position.z = 0.0f;
  p->m_healthBar = healthBar;
  // p->SetTint({1.0f, 0.0f, 0.0f, 1.0f});
  m_players[0] = p;
  AddChild(p);


  s = GET_FACTORY->CreateObject<game::PunchingBag>("PunchingBag");
  s->transform.position.x = -278;
  s->transform.position.y = -10;
  s->transform.position.z = 10;
  AddChild(s);

  s2 = GET_FACTORY->CreateObject<game::PunchingBag>("PunchingBag");
  s2->transform.position.x = 425;
  s2->transform.position.y = -93;
  s2->transform.position.z = 93;
  AddChild(s2);


  s3 = GET_FACTORY->CreateObject<game::PunchingBag>("PunchingBag");
  s3->transform.position.x = 480;
  s3->transform.position.y = -155;
  s3->transform.position.z = 155;
  AddChild(s3);

#ifndef DEBUG_CAMERA
  dynamic_cast<Sigma::CameraFollow*>(GET_CAMERA->GetCurrentCamera())->m_targetP1 = p;
#endif
}
void PrototypeScene::Update(double delta) {
  GameScene::Update(delta);

  // If pressed key 2 create 2nd player
  if (AEInputGamepadButtonTriggered(0, 0x0010)) {
    // Check to avoid having infinite player 2 objects -x
    if (m_players[1]) return;

    healthBar2 = GET_FACTORY->CreateObject<game::HealthBar>("Progress");
    healthBar2->m_screenSpaceTransform.scale = {300, 20};
    healthBar2->m_screenSpaceTransform.position = {0, 500, 0};
    healthBar2->m_progress = 1;
    healthBar2->SetTexture("assets/core/debug_green.png");

    p2 = GET_FACTORY->CreateObject<game::Player>("Player2", 0, "assets/characters/player/behaviour.json");
    p2->transform.position.x = m_playerStartPos.x;
    p2->transform.position.y = m_playerStartPos.y;
    p2->transform.position.z = 0.0f;
    p2->m_healthBar = healthBar2;
    dynamic_cast<Sigma::CameraFollow *>(GET_CAMERA->GetCurrentCamera())->m_targetP2 = p2;
    m_players[1] = p2;
    AddChild(p2);
    AddChild(healthBar2);
  }

  if (!m_players[0] && !m_players[1]) {
    GET_MANAGER->LoadScene(m_deadScene);
    GET_MANAGER->UnloadScene(0u);
  }
}
void PrototypeScene::Free() {
  GameScene::Free();

}


} // namespace game
