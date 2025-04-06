#include "Scene3.hpp"
#include "Core.hpp"
#include "Factory.hpp"
#include "Objects/Actor.hpp"
#include "Objects/Destructibles/Box.hpp"
#include "Scene4.hpp"

#define DEBUG_CAMERA

namespace game {

void Scene3::Load() {

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

  m_exitLocationDoor = GET_FACTORY->CreateObject<Door>("Exit_Door", 2);
  m_exitLocationDoor->transform.position = {496, -79, 79};
  AddChild(m_exitLocationDoor);

  auto b1 = GET_FACTORY->CreateObject<Box>("Machine1");
  b1->transform.position = {-250, 9, -9};

  auto b2 = GET_FACTORY->CreateObject<Box>("Machine2");
  b2->transform.position = {200, 10, -10};

  auto Sdoor1 = GET_FACTORY->CreateObject<Door>("Spawner_Door1", 1);
  Sdoor1->transform.position = {-293, 54, -54};
  AddChild(Sdoor1);
  m_spawnerDoors.push_back(Sdoor1);

  auto Sdoor2 = GET_FACTORY->CreateObject<Door>("Spawner_Door2", 1);
  Sdoor2->transform.position = {-5, 54, -54};
  AddChild(Sdoor2);
  m_spawnerDoors.push_back(Sdoor2);

  auto Sdoor3 = GET_FACTORY->CreateObject<Door>("Spawner_Door3", 2);
  Sdoor3->transform.position = {264, -8, 8};
  AddChild(Sdoor3);
  m_spawnerDoors.push_back(Sdoor3);

  m_spawnerDoors.emplace_back(m_exitLocationDoor);

  AddChild(b1);
  AddChild(b2);

  GameScene::Load();

  SetNextScene(new Scene4("Game Scene 4", 4, "assets/level-1/scene-4.json"));
}

void Scene3::Update(double delta) {
  GameScene::Update(delta);
}
void Scene3::Free() {
  GameScene::Free();
}

}
