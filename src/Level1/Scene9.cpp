#include "Scene9.hpp"
#include "Core.hpp"
#include "Factory.hpp"
#include "Objects/Actor.hpp"
#include "Objects/Destructibles/Box.hpp"
#include "Scene7.hpp"

#define DEBUG_CAMERA

namespace game {

void Scene9::Load() {

  floor = GET_FACTORY->CreateObject<Sigma::Actor>();
  floor->SetTexture("assets/level-1/scene-9-floor.png");
  floor->transform.scale = {957.0f, 405.0f};
  floor->transform.position.z = -5000;
  AddChild(floor);

  walls = GET_FACTORY->CreateObject<Sigma::Actor>();
  walls->SetTexture("assets/level-1/scene-9-walls.png");
  walls->transform.scale = {957.0f, 405.0f};
  walls->transform.position.z = -5000;
  AddChild(walls);

  m_exitLocationDoor = GET_FACTORY->CreateObject<Door>("Exit_Door", 4);
  m_exitLocationDoor->transform.position = {306, -81, 81};
  AddChild(m_exitLocationDoor);

  auto Sdoor1 = GET_FACTORY->CreateObject<Door>("Spawner_Door1", 2);
  Sdoor1->transform.position = {-274, 82, -82};
  AddChild(Sdoor1);
  m_spawnerDoors.push_back(Sdoor1);

  auto Sdoor2 = GET_FACTORY->CreateObject<Door>("Spawner_Door2", 1);
  Sdoor2->transform.position = {-106, -37, 37};
  AddChild(Sdoor2);
  m_spawnerDoors.push_back(Sdoor2);

  auto Sdoor3 = GET_FACTORY->CreateObject<Door>("Spawner_Door3", 2);
  Sdoor3->transform.position = {10, -74, 74};
  AddChild(Sdoor3);
  m_spawnerDoors.push_back(Sdoor3);

  auto Sdoor4 = GET_FACTORY->CreateObject<Door>("Spawner_Door4", 2);
  Sdoor4->transform.position = {442, -122, 122};
  AddChild(Sdoor4);
  m_spawnerDoors.push_back(Sdoor4);

  auto b1 = GET_FACTORY->CreateObject<Box>("Machine1");
  b1->transform.position = {-219, -21, 21};

  AddChild(b1);

  auto b2 = GET_FACTORY->CreateObject<Box>("Machine2");
  b2->transform.position = {-188, -52, 52};

  AddChild(b2);

  m_spawnerDoors.emplace_back(m_exitLocationDoor);

  GameScene::Load();

  SetNextScene(new Scene7("Game Scene 7", 7, "assets/level-1/scene-7.json"));
}

void Scene9::Update(double delta) {
  GameScene::Update(delta);
}
void Scene9::Free() {
  GameScene::Free();
}

}