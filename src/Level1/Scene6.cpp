#include "Scene6.hpp"
#include "Controller/CameraController.hpp"
#include "Core.hpp"
#include "Factory.hpp"
#include "GameManager.hpp"
#include "Objects/Actor.hpp"
#include "Objects/Camera.hpp"
#include "Objects/Destructibles/Box.hpp"
#include "Scene9.hpp"

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

  m_exitLocationDoor = GET_FACTORY->CreateObject<Door>("Exit_Door", 3);
  m_exitLocationDoor->transform.position = {296, -115, 115};
  AddChild(m_exitLocationDoor);

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

  auto overlay = GET_FACTORY->CreateObject<Sigma::Actor>();
  overlay->SetTexture("assets/level-1/scene-6-overlay.png");
  overlay->transform.scale = {953.0f, 538.0f};
  overlay->transform.position.z = 5000;
  AddChild(overlay);

  auto b1 = GET_FACTORY->CreateObject<Box>("Machine1");
  b1->transform.position = {-236, 108, -108};

  AddChild(b1);

  m_spawnerDoors.emplace_back(m_exitLocationDoor);

  GameScene::Load();

  SetNextScene(new Scene9("Game Scene 9", 9, "assets/level-1/scene-9.json"));
}

void Scene6::Update(double delta) {
  GameScene::Update(delta);
}
void Scene6::Free() {
  GameScene::Free();
}

}
