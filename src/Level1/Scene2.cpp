#include "Scene2.hpp"
#include "Controller/CameraController.hpp"
#include "Core.hpp"
#include "Factory.hpp"
#include "GameManager.hpp"
#include "Objects/Actor.hpp"
#include "Objects/Camera.hpp"
#include "Scene3.hpp"

#define DEBUG_CAMERA

namespace game {

void Scene2::Load() {
  GameScene::Load();

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

  SetNextScene(new Scene3("Game Scene 3", 3, "assets/level-1/scene-3.json"));
}

void Scene2::Update(double delta) {
  GameScene::Update(delta);
}
void Scene2::Free() {
  GameScene::Free();
}

}
