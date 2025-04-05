#include "Scene8.hpp"
#include "Core.hpp"
#include "Factory.hpp"
#include "Objects/Actor.hpp"
#include "Objects/Destructibles/Box.hpp"
#include "Scene5.hpp"

#define DEBUG_CAMERA

namespace game {

void Scene8::Load() {

  floor = GET_FACTORY->CreateObject<Sigma::Actor>();
  floor->SetTexture("assets/level-1/scene-8-floor.png");
  floor->transform.scale = {1013.0f, 321.0f};
  floor->transform.position.z = -5000;
  AddChild(floor);

  walls = GET_FACTORY->CreateObject<Sigma::Actor>();
  walls->SetTexture("assets/level-1/scene-8-walls.png");
  walls->transform.scale = {1013.0f, 321.0f};
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

  SetNextScene(new Scene5("Game Scene 5", 5, "assets/level-1/scene-5.json"));
}

void Scene8::Update(double delta) {
  GameScene::Update(delta);
}
void Scene8::Free() {
  GameScene::Free();
}

}