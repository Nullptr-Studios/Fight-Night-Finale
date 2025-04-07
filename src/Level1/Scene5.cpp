#include "Scene5.hpp"
#include "Controller/CameraController.hpp"
#include "Core.hpp"
#include "Factory.hpp"
#include "GameManager.hpp"
#include "Objects/Actor.hpp"
#include "Objects/Camera.hpp"
#include "Objects/Destructibles/Box.hpp"
#include "Scene6.hpp"

#define DEBUG_CAMERA

namespace game {

void Scene5::Load() {

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

  m_exitLocationDoor = GET_FACTORY->CreateObject<Door>("Exit_Door", 2);
  m_exitLocationDoor->transform.position = {706, -97, 79};
  AddChild(m_exitLocationDoor);

  auto b1 = GET_FACTORY->CreateObject<Box>("Machine1");
  b1->transform.position = {292, -82, 82};

  auto Sdoor1 = GET_FACTORY->CreateObject<Door>("Spawner_Door1", 1);
  Sdoor1->transform.position = {-566, 71, -71};
  AddChild(Sdoor1);
  m_spawnerDoors.push_back(Sdoor1);

  auto Sdoor2 = GET_FACTORY->CreateObject<Door>("Spawner_Door2", 1);
  Sdoor2->transform.position = {-150, -25, 25};
  AddChild(Sdoor2);
  m_spawnerDoors.push_back(Sdoor2);

  auto Sdoor3 = GET_FACTORY->CreateObject<Door>("Spawner_Door3", 1);
  Sdoor3->transform.position = {-54, -25, 25};
  AddChild(Sdoor3);
  m_spawnerDoors.push_back(Sdoor3);

  auto Sdoor4 = GET_FACTORY->CreateObject<Door>("Spawner_Door4", 1);
  Sdoor4->transform.position = {42, -25, 25};
  AddChild(Sdoor4);
  m_spawnerDoors.push_back(Sdoor4);

  auto Sdoor5 = GET_FACTORY->CreateObject<Door>("Spawner_Door5", 1);
  Sdoor5->transform.position = {138, -25, 25};
  AddChild(Sdoor5);
  m_spawnerDoors.push_back(Sdoor5);

  auto Sdoor6 = GET_FACTORY->CreateObject<Door>("Spawner_Door6", 1);
  Sdoor6->transform.position = {234, -25, 25};
  AddChild(Sdoor6);
  m_spawnerDoors.push_back(Sdoor6);

  auto Sdoor7 = GET_FACTORY->CreateObject<Door>("Spawner_Door7", 1);
  Sdoor7->transform.position = {410, -73, 73};
  AddChild(Sdoor7);
  m_spawnerDoors.push_back(Sdoor7);

  auto Sdoor8 = GET_FACTORY->CreateObject<Door>("Spawner_Door8", 1);
  Sdoor8->transform.position = {506, -73, 73};
  AddChild(Sdoor8);
  m_spawnerDoors.push_back(Sdoor8);

  auto Sdoor9 = GET_FACTORY->CreateObject<Door>("Spawner_Door9", 1);
  Sdoor9->transform.position = {602, -73, 73};
  AddChild(Sdoor9);
  m_spawnerDoors.push_back(Sdoor9);

  m_spawnerDoors.emplace_back(m_exitLocationDoor);

  AddChild(b1);

  GameScene::Load();

  SetNextScene(new Scene6("Game Scene 6", 6, "assets/level-1/scene-6.json"));
}

void Scene5::Update(double delta) {
  GameScene::Update(delta);
}
void Scene5::Free() {
  GameScene::Free();
}

}
