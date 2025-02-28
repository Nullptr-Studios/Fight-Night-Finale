#include "Scene2.hpp"
#include <sstream>
#include "Controller/CameraController.hpp"
#include "Objects/Camera.hpp"
#include "core.hpp"
#include "Factory.hpp"
#include "GameManager.hpp"
#include "Objects/Actor.hpp"

#define DEBUG_CAMERA

namespace game {

void Scene2::Load() {
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
  floor->SetTexture("assets/level-1/scene-2-floor.png");
  floor->transform.scale = {1185.0f, 429.0f};
  floor->transform.position.z = -5000;
  AddChild(floor);

  walls = GET_FACTORY->CreateObject<Sigma::Actor>();
  walls->SetTexture("assets/level-1/scene-2-walls.png");
  walls->transform.scale = {1185.0f, 429.0f};
  walls->transform.position.z = -5000;
  AddChild(walls);

  std::array<Sigma::Actor*, 15> stupidThings = {};
  for (int i = 0; i < 15; i++) {
    std::stringstream ss;
    ss << "Thing " << i;
    stupidThings[i] = GET_FACTORY->CreateObject<Sigma::Actor>(ss.str());
    stupidThings[i]->transform.scale = {10.0f/2, 10.0f/2};
    stupidThings[i]->SetTint({1.0f, 0.0f, 1.0f, 1.0f});
  }
}

void Scene2::Update(double delta) {
  GameScene::Update(delta);
}
void Scene2::Free() {
  GameScene::Free();
}

}
