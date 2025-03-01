#include "Scene1.hpp"
#include "Controller/CameraController.hpp"
#include "Core.hpp"
#include "Factory.hpp"
#include "GameManager.hpp"
#include "Objects/Actor.hpp"
#include "Objects/Camera.hpp"
#include "Objects/CameraFollow.hpp"

// #define DEBUG_CAMERA

namespace game {

void Scene1::Load() {
  GameScene::Load();

  floor = GET_FACTORY->CreateObject<Sigma::Actor>();
  floor->SetTexture("assets/level-1/scene-1-floor.png");
  floor->transform.scale = {761.0f, 281.0f};
  floor->transform.position.z = -5000;
  AddChild(floor);

  walls = GET_FACTORY->CreateObject<Sigma::Actor>();
  walls->SetTexture("assets/level-1/scene-1-walls.png");
  walls->transform.scale = {761.0f, 281.0f};
  walls->transform.position.z = -5000;
  AddChild(walls);
}

void Scene1::Update(double delta) {
  GameScene::Update(delta);
}
void Scene1::Free() {
  GameScene::Free();
}

}
