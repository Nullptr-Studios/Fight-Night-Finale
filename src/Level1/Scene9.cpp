#include "Scene9.hpp"
#include "Core.hpp"
#include "Factory.hpp"
#include "Objects/Actor.hpp"
#include "Objects/Destructibles/Box.hpp"
#include "Scene7.hpp"
#include "UI/WinScene.hpp"

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

  m_exitLocationDoor = GET_FACTORY->CreateObject<Door>("Exit_Door", 2);
  m_exitLocationDoor->transform.position = {496, -79, 79};
  AddChild(m_exitLocationDoor);

  auto Sdoor1 = GET_FACTORY->CreateObject<Door>("Spawner_Door1", 1);
  Sdoor1->transform.position = {-293, 54, -54};
  AddChild(Sdoor1);
  m_spawnerDoors.push_back(Sdoor1);

  m_spawnerDoors.emplace_back(m_exitLocationDoor);

  GameScene::Load();

  SetNextScene(new WinScene("Win Scene", 7));
}

void Scene9::Update(double delta) {
  GameScene::Update(delta);
}
void Scene9::Free() {
  GameScene::Free();
}

}