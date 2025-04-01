#include "Scene6.hpp"
#include "Controller/CameraController.hpp"
#include "Core.hpp"
#include "Factory.hpp"
#include "GameManager.hpp"
#include "Objects/Actor.hpp"
#include "Objects/Camera.hpp"
#include "Objects/Destructibles/Box.hpp"
#include "Scene7.hpp"
#include "UI/WinScene.hpp"

#define DEBUG_CAMERA

namespace game {

void Scene6::Load() {

  floor = GET_FACTORY->CreateObject<Sigma::Actor>();
  floor->SetTexture("assets/level-1/scene-6-floor.png");
  floor->transform.scale = {953.0f, 538.0f};
  floor->transform.position.z = -5000;
  AddChild(floor);

  walls = GET_FACTORY->CreateObject<Sigma::Actor>();
  walls->SetTexture("assets/level-1/scene-6-walls.png");
  walls->transform.scale = {953.0f, 538.0f};
  walls->transform.position.z = -5000;
  AddChild(walls);

  GameScene::Load();

  SetNextScene(new WinScene("Win Scene", 7));
}

void Scene6::Update(double delta) {
  GameScene::Update(delta);
}
void Scene6::Free() {
  GameScene::Free();
}

}
