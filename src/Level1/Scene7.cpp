#include "Scene7.hpp"
#include "Controller/CameraController.hpp"
#include "Core.hpp"
#include "Factory.hpp"
#include "GameManager.hpp"
#include "Objects/Actor.hpp"
#include "Objects/Camera.hpp"
#include "UI/WinScene.hpp"

#define DEBUG_CAMERA

namespace game {

void Scene7::Load() {

  floor = GET_FACTORY->CreateObject<Sigma::Actor>();
  floor->SetTexture("assets/level-1/scene-7-floor.png");
  floor->transform.scale = {757.0f, 261.0f};
  floor->transform.position = {-282, -22, -5000};
  AddChild(floor);

  walls = GET_FACTORY->CreateObject<Sigma::Actor>();
  walls->SetTexture("assets/level-1/scene-7-walls.png");
  walls->transform.scale = {757.0f, 261.0f};
  walls->transform.position = {-282, -22, -5000};
  AddChild(walls);

  GameScene::Load();

  GameplayManager::GetInstance()->BossMusic();

  SetNextScene(new WinScene("Win Scene", 7));
}

void Scene7::Update(double delta) {
  GameScene::Update(delta);
}
void Scene7::Free() {
  GameScene::Free();
}

}
