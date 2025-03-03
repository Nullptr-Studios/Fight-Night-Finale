#include "Scene5.hpp"
#include "Controller/CameraController.hpp"
#include "Core.hpp"
#include "Factory.hpp"
#include "GameManager.hpp"
#include "Objects/Actor.hpp"
#include "Objects/Camera.hpp"
#include "Scene6.hpp"

#define DEBUG_CAMERA

namespace game {

void Scene5::Load() {
  GameScene::Load();

  floor = GET_FACTORY->CreateObject<Sigma::Actor>();
  floor->SetTexture("assets/level-1/scene-5-floor.png");
  floor->transform.scale = {1485.0f, 333.0f};
  floor->transform.position.z = -5000;
  AddChild(floor);

  walls = GET_FACTORY->CreateObject<Sigma::Actor>();
  walls->SetTexture("assets/level-1/scene-5-walls.png");
  walls->transform.scale = {1485.0f, 333.0f};
  walls->transform.position.z = -5000;
  AddChild(walls);

  SetNextScene(new Scene6("Game Scene 6", 6, "assets/level-1/scene-6.json"));
}

void Scene5::Update(double delta) {
  GameScene::Update(delta);
}
void Scene5::Free() {
  GameScene::Free();
}

}
