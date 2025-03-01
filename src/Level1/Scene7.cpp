#include "Scene7.hpp"
#include "Controller/CameraController.hpp"
#include "Objects/Camera.hpp"
#include "Core.hpp"
#include "Factory.hpp"
#include "GameManager.hpp"
#include "Objects/Actor.hpp"

#define DEBUG_CAMERA

namespace game {

void Scene7::Load() {
  GameScene::Load();

#ifdef DEBUG_CAMERA
  GET_CAMERA->SetCurrentCamera(GET_FACTORY->CreateObject<Sigma::Camera>("Debug Camera"));
  GET_CAMERA->GetCurrentCamera()->size = 1;
#else
  GET_CAMERA->SetCurrentCamera(GET_FACTORY->CreateObject<Sigma::CameraFollow>("Main Camera"));
  GET_CAMERA->GetCurrentCamera()->size = 2;
#endif

  AddChild(GET_CAMERA->GetCurrentCamera());

  floor = GET_FACTORY->CreateObject<Sigma::Actor>();
  floor->SetTexture("assets/level-1/scene-7-floor.png");
  floor->transform.scale = {2000.0f, 2000.0f};
  floor->transform.position.z = -5000;
  AddChild(floor);

  walls = GET_FACTORY->CreateObject<Sigma::Actor>();
  walls->SetTexture("assets/level-1/scene-7-walls.png");
  walls->transform.scale = {2000.0f, 2000.0f};
  walls->transform.position.z = -5000;
  AddChild(walls);
}

void Scene7::Update(double delta) {
  GameScene::Update(delta);
}
void Scene7::Free() {
  GameScene::Free();
}

}
