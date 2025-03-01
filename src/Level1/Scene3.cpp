#include "Scene3.hpp"
#include "Controller/CameraController.hpp"
#include "Objects/Camera.hpp"
#include "Core.hpp"
#include "Factory.hpp"
#include "GameManager.hpp"
#include "Objects/Actor.hpp"

#define DEBUG_CAMERA

namespace game {

void Scene3::Load() {
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
  floor->SetTexture("assets/level-1/scene-3-floor.png");
  floor->transform.scale = {1066.0f, 298.0f};
  floor->transform.position.z = -5000;
  AddChild(floor);

  walls = GET_FACTORY->CreateObject<Sigma::Actor>();
  walls->SetTexture("assets/level-1/scene-3-walls.png");
  walls->transform.scale = {1066.0f, 298.0f};
  walls->transform.position.z = -5000;
  AddChild(walls);
}

void Scene3::Update(double delta) {
  GameScene::Update(delta);
}
void Scene3::Free() {
  GameScene::Free();
}

}
