#include "Scene4.hpp"
#include "Core.hpp"
#include "Factory.hpp"
#include "Objects/Actor.hpp"
#include "Objects/Destructibles/Box.hpp"
#include "Scene5.hpp"


namespace game {

void Scene4::Load() {

  walls = GET_FACTORY->CreateObject<Sigma::Actor>("walls");
  walls->SetTexture("assets/level-1/scene-4-walls.png");
  walls->transform.scale = {933.0f, 273.0f};
  walls->transform.position.z = -4999;
  AddChild(walls);

  floor = GET_FACTORY->CreateObject<Sigma::Actor>("floor");
  floor->SetTexture("assets/level-1/scene-4-floor.png");
  floor->transform.scale = {933.0f, 273.0f};
  floor->transform.position.z = -5000;
  AddChild(floor);

  m_exitLocationDoor = GET_FACTORY->CreateObject<Door>("Exit_Door", 2);
  m_exitLocationDoor->transform.position = {370, -7, 7};
  AddChild(m_exitLocationDoor);

  auto b1 = GET_FACTORY->CreateObject<Box>("Machine1");
  b1->transform.position = {400, -88, 88};

  AddChild(b1);

  auto Sdoor1 = GET_FACTORY->CreateObject<Door>("Spawner_Door1", 1);
  Sdoor1->transform.position = {-206, 41, -41};
  AddChild(Sdoor1);
  m_spawnerDoors.push_back(Sdoor1);

  auto Sdoor2 = GET_FACTORY->CreateObject<Door>("Spawner_Door2", 1);
  Sdoor2->transform.position = {267, 17, -17};
  AddChild(Sdoor2);
  m_spawnerDoors.push_back(Sdoor2);

  m_spawnerDoors.emplace_back(m_exitLocationDoor);

  GameScene::Load();

  SetNextScene(new Scene5("Game Scene 5", 5, "assets/level-1/scene-5.json"));
}

void Scene4::Update(double delta) {
  GameScene::Update(delta);
}
void Scene4::Free() {
  GameScene::Free();
}

}
