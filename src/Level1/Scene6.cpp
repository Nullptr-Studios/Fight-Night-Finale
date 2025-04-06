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

  auto Sdoor1 = GET_FACTORY->CreateObject<Door>("Spawner_Door1", 2);
  Sdoor1->transform.position = {-64, 112, -112};
  AddChild(Sdoor1);
  m_spawnerDoors.push_back(Sdoor1);

  auto Sdoor2 = GET_FACTORY->CreateObject<Door>("Spawner_Door2", 2);
  Sdoor2->transform.position = {32, 16, -16};
  AddChild(Sdoor2);
  m_spawnerDoors.push_back(Sdoor2);

  auto Sdoor3 = GET_FACTORY->CreateObject<Door>("Spawner_Door3", 2);
  Sdoor3->transform.position = {140, -92, 92};
  AddChild(Sdoor3);
  m_spawnerDoors.push_back(Sdoor3);

  auto Sdoor4 = GET_FACTORY->CreateObject<Door>("Spawner_Door4", 2);
  Sdoor4->transform.position = {440, -200, 200};
  AddChild(Sdoor4);
  m_spawnerDoors.push_back(Sdoor4);

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
