#include "Scene4.hpp"
#include "Controller/CameraController.hpp"
#include "Core.hpp"
#include "Factory.hpp"
#include "GameManager.hpp"
#include "Objects/Actor.hpp"
#include "Objects/Camera.hpp"
#include "Scene5.hpp"


namespace game {

void Scene4::Load() {
  GameScene::Load();

  floor = GET_FACTORY->CreateObject<Sigma::Actor>();
  floor->SetTexture("assets/level-1/scene-4-floor.png");
  floor->transform.scale = {933.0f, 273.0f};
  floor->transform.position.z = -5000;
  AddChild(floor);

  walls = GET_FACTORY->CreateObject<Sigma::Actor>();
  walls->SetTexture("assets/level-1/scene-4-walls.png");
  walls->transform.scale = {933.0f, 273.0f};
  walls->transform.position.z = -5000;
  AddChild(walls);

  SetNextScene(new Scene5("Game Scene 5", 5, "assets/level-1/scene-5.json"));
}

void Scene4::Update(double delta) {
  GameScene::Update(delta);
}
void Scene4::Free() {
  GameScene::Free();
}

}
