#include "Controller/CameraController.hpp"
#include "Core.hpp"
#include "Enemies/DefaultEnemy.hpp"
#include "Enemies/Enemy.hpp"
#include "Factory.hpp"
#include "GameManager.hpp"
#include "Level1_Scene.hpp"
#include "Objects/Actor.hpp"
#include "Objects/CameraFollow.hpp"
#include "Objects/Debug/PunchingBag.hpp"
#include "Player/Player.hpp"
#include "UI/HealthBar.hpp"
#include "UI/MainMenu.hpp"
#include "core.hpp"

// #define DEBUG_CAMERA

namespace game {

void Level1_Scene::Load() {
  m_debug = true;
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
  floor->SetTexture("assets/level-1/scene-2-floor.png");
  floor->transform.scale = {1185.0f, 429.0f};
  floor->transform.position.z = -5000;
  AddChild(floor);

  walls = GET_FACTORY->CreateObject<Sigma::Actor>();
  walls->SetTexture("assets/level-1/scene-2-walls.png");
  walls->transform.scale = {1185.0f, 429.0f};
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
  p->SetTint({1.0f, 0.0f, 0.0f, 1.0f});
  m_players[0] = p;
  AddChild(p);


#ifndef DEBUG_CAMERA
  dynamic_cast<Sigma::CameraFollow*>(GET_CAMERA->GetCurrentCamera())->m_targetP1 = p;
#endif
}
void Level1_Scene::Update(double delta) {
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
void Level1_Scene::Free() {
  GameScene::Free();

}


} // namespace game
