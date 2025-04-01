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
  GameScene::Load();

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
  m_exitLocationDoor->transform.position = {706, -79, 79};
  AddChild(m_exitLocationDoor);

  auto b1 = GET_FACTORY->CreateObject<Box>("Machine1");
  b1->transform.position = {276, -67, 67};

  AddChild(b1);


  SetNextScene(new Scene6("Game Scene 6", 6, "assets/level-1/scene-6.json"));
}

void Scene5::Update(double delta) {
  GameScene::Update(delta);
}
void Scene5::Free() {
  GameScene::Free();
}

}
