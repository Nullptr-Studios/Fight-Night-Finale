#include "Scene2.hpp"
#include "Controller/CameraController.hpp"
#include "Core.hpp"
#include "Factory.hpp"
#include "GameManager.hpp"
#include "Objects/Actor.hpp"
#include "Objects/Camera.hpp"
#include "Objects/Destructibles/Box.hpp"
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

  m_exitLocationDoor = GET_FACTORY->CreateObject<Door>("Exit_Door", 3);
  m_exitLocationDoor->transform.position = {448, -132, 132};
  AddChild(m_exitLocationDoor);
  
  auto b1 = GET_FACTORY->CreateObject<Box>("Machine1");
  b1->transform.position = {111, 58, -58};

  auto b2 = GET_FACTORY->CreateObject<Box>("Machine2");
  b2->transform.position = {557, -195, 195};

  auto Sdoor1 = GET_FACTORY->CreateObject<Door>("Spawner_Door1", 1);
  Sdoor1->transform.position = {-428, 119, -119};
  AddChild(Sdoor1);
  m_spawnerDoors.emplace_back(Sdoor1);

  auto Sdoor2 = GET_FACTORY->CreateObject<Door>("Spawner_Door2", 1);
  Sdoor2->transform.position = {-172, 119, -119};
  AddChild(Sdoor2);
  m_spawnerDoors.emplace_back(Sdoor2);

  auto Sdoor3 = GET_FACTORY->CreateObject<Door>("Spawner_Door3", 2);
  Sdoor3->transform.position = {148, 72, -72};
  AddChild(Sdoor3);
  m_spawnerDoors.emplace_back(Sdoor3);

  m_spawnerDoors.emplace_back(m_exitLocationDoor);
  AddChild(b1);
  AddChild(b2);

  SetNextScene(new Scene3("Game Scene 3", 3, "assets/level-1/scene-3.json"));
}

void Scene2::Update(double delta) {
  GameScene::Update(delta);
}
void Scene2::Free() {
  GameScene::Free();
}

}
