#include "PrototypeScene.hpp"
#include "Controller/CameraController.hpp"
#include "Core.hpp"
#include "Enemies/Enemy.hpp"
#include "Factory.hpp"
#include "Objects/Actor.hpp"
#include "Objects/Camera.hpp"
#include "Player/Player.hpp"

namespace game {

void PrototypeScene::Load() {
  std::cout << "PrototypeScene::Load()" << std::endl;

  auto camera = GET_FACTORY->CreateObject<Sigma::Camera>("Camera");
  camera->size = 2;
  GET_CAMERA->SetCurrentCamera(camera);

  auto* floor = GET_FACTORY->CreateObject<Sigma::Actor>("Floor");
  floor->SetTexture("assets/prototype-scene-2/t-floor.png");
  floor->transform.scale = {1061.0f, 346.0f};
  auto* walls = GET_FACTORY->CreateObject<Sigma::Actor>("Walls");
  walls->SetTexture("assets/prototype-scene-2/t-walls.png");
  walls->transform.scale = {1061.0f, 346.0f};

  auto p = GET_FACTORY->CreateObject<game::Player>("Player");
  p->SetTexture("assets/prototype-scene/T_Walls.png");
  p->SetJsonPath("assets/characters/dummy.json");
  p->transform.scale = {32.0f, 64.0f};

  auto e = GET_FACTORY->CreateObject<game::Enemy>("Enemy");
  e->transform.position = { 400.0f, 0.0f, 0.0f };
  e->SetJsonPath("assets/characters/dummy.json");
  e->transform.scale = {32.0f, 64.0f};
}

}
