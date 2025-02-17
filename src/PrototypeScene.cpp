#include "PrototypeScene.hpp"
#include "Controller/CameraController.hpp"
#include "Core.hpp"
#include "Enemies/Enemy.hpp"
#include "Factory.hpp"
#include "Objects/Actor.hpp"
#include "Objects/CameraFollow.hpp"
#include "Objects/Debug/PunchingBag.hpp"
#include "Player/Player.hpp"

#define DEBUG_CAMERA

namespace game {

void PrototypeScene::Load() {
  GameScene::Load();
  std::cout << "PrototypeScene::Load()" << std::endl;

#ifdef DEBUG_CAMERA
  GET_CAMERA->SetCurrentCamera(GET_FACTORY->CreateObject<Sigma::Camera>("Debug Camera"));
  GET_CAMERA->GetCurrentCamera()->size = 1;
#else
  GET_CAMERA->SetCurrentCamera(GET_FACTORY->CreateObject<Sigma::CameraFollow>("Main Camera"));
  GET_CAMERA->GetCurrentCamera()->size = 2;
#endif

  auto *floor = GET_FACTORY->CreateObject<Sigma::Actor>();
  floor->SetTexture("assets/prototype-scene-2/t-floor.png");
  floor->transform.scale = {1061.0f, 346.0f};
  floor->transform.position.z = -5000;

  auto *walls = GET_FACTORY->CreateObject<Sigma::Actor>();
  walls->SetTexture("assets/prototype-scene-2/t-walls.png");
  walls->transform.scale = {1061.0f, 346.0f};
  walls->transform.position.z = -5000;

  auto p = GET_FACTORY->CreateObject<game::Player>("Player", -1, "assets/characters/player/behaviour.json");
  p->transform.position.x = m_playerStartPos.x;
  p->transform.position.y = m_playerStartPos.y;
  p->transform.position.z = 0.0f;


  auto s = GET_FACTORY->CreateObject<game::PunchingBag>("PunchingBag");
  s->transform.position.x = -278;
  s->transform.position.y = -10;
  s->transform.position.z = 10;

  m_players.push_back(p);

#ifndef DEBUG_CAMERA
  dynamic_cast<Sigma::CameraFollow*>(GET_CAMERA->GetCurrentCamera())->m_targetP1 = p;
#endif
}
void PrototypeScene::Update(double delta) {
  GameScene::Update(delta);

  // If pressed key 2 create 2nd player
  if (AEInputGamepadButtonTriggered(0, 0x0010)) {
    // Check to avoid having infinite player 2 objects -x
    if (m_players.size() >= 2) return;

    auto p2 = GET_FACTORY->CreateObject<game::Player>("Player2", 0, "assets/characters/player/behaviour.json");
    p2->transform.position.x = m_playerStartPos.x;
    p2->transform.position.y = m_playerStartPos.y;
    p2->transform.position.z = 0.0f;
    dynamic_cast<Sigma::CameraFollow*>(GET_CAMERA->GetCurrentCamera())->m_targetP2 = p2;
    m_players.push_back(p2);
  }

}

  
}
