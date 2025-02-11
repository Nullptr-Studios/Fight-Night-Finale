#include "PrototypeScene.hpp"
#include "Controller/CameraController.hpp"
#include "Core.hpp"
#include "Factory.hpp"
#include "Objects/Camera.hpp"
#include "Objects/Actor.hpp"

#include "Objects/Debug/PunchingBag.hpp"
#include "Player/Player.hpp"

namespace game {

void PrototypeScene::Load() {
  GameScene::Load();
  std::cout << "PrototypeScene::Load()" << std::endl;

  GET_CAMERA->SetCurrentCamera(GET_FACTORY->CreateObject<Sigma::Camera>("Main Camera"));
  GET_CAMERA->GetCurrentCamera()->size = 2;

  auto* floor = GET_FACTORY->CreateObject<Sigma::Actor>();
  floor->SetTexture("assets/prototype-scene-2/t-floor.png");
  floor->transform.scale = {1061.0f, 346.0f};
  floor->transform.position.z = -5000;
  
  auto* walls = GET_FACTORY->CreateObject<Sigma::Actor>();
  walls->SetTexture("assets/prototype-scene-2/t-walls.png");
  walls->transform.scale = {1061.0f, 346.0f};
  walls->transform.position.z = -5000;

  auto p = GET_FACTORY->CreateObject<game::Player>("Player", -1, "assets/characters/dummy.json");
  p->transform.position.y = -128;

  auto s = GET_FACTORY->CreateObject<game::PunchingBag>("PunchingBag");
  s->transform.position.y = -128;
  s->transform.position.z = 128;

}

}
