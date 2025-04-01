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
