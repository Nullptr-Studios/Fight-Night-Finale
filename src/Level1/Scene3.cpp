#include "Scene3.hpp"
#include "Controller/CameraController.hpp"
#include "Core.hpp"
#include "Factory.hpp"
#include "GameManager.hpp"
#include "Objects/Actor.hpp"
#include "Objects/Camera.hpp"
#include "Scene4.hpp"

#define DEBUG_CAMERA

namespace game {

void Scene3::Load() {
  GameScene::Load();

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

  SetNextScene(new Scene4("Game Scene 4", 4, "assets/level-1/scene-4.json"));
}

void Scene3::Update(double delta) {
  GameScene::Update(delta);
}
void Scene3::Free() {
  GameScene::Free();
}

}
