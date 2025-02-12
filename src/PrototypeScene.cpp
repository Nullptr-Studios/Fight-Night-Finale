#include "PrototypeScene.hpp"
#include "Controller/CameraController.hpp"
#include "Core.hpp"
#include "Factory.hpp"
#include "Objects/Actor.hpp"
#include "Objects/CameraFollow.hpp"

#include "Objects/Debug/PunchingBag.hpp"
#include "Player/Player.hpp"

namespace game {

void PrototypeScene::Load() {
  GameScene::Load();
  std::cout << "PrototypeScene::Load()" << std::endl;

  GET_CAMERA->SetCurrentCamera(GET_FACTORY->CreateObject<Sigma::CameraFollow>("Main Camera"));
  GET_CAMERA->GetCurrentCamera()->size = 2;

  auto *floor = GET_FACTORY->CreateObject<Sigma::Actor>();
  floor->SetTexture("assets/prototype-scene-2/t-floor.png");
  floor->transform.scale = {1061.0f, 346.0f};
  floor->transform.position.z = -5000;

  auto *walls = GET_FACTORY->CreateObject<Sigma::Actor>();
  walls->SetTexture("assets/prototype-scene-2/t-walls.png");
  walls->transform.scale = {1061.0f, 346.0f};
  walls->transform.position.z = -5000;

  auto p = GET_FACTORY->CreateObject<game::Player>("Player", -1, "assets/characters/dummy.json");
  p->transform.position.y = -128;

  auto s = GET_FACTORY->CreateObject<game::PunchingBag>("PunchingBag");
  s->transform.position.y = -128;
  s->transform.position.z = 128;

  
  dynamic_cast<Sigma::CameraFollow*>(GET_CAMERA->GetCurrentCamera())->m_targetP1 = p;
}
void PrototypeScene::Update(double delta) {
  GameScene::Update(delta);

  // If pressed key 2 create 2nd player
  if (AEInputKeyTriggered('2')) {
    auto p2 = GET_FACTORY->CreateObject<game::Player>("Player2", 0, "assets/characters/dummy.json");
    p2->transform.position.y = -128;
    dynamic_cast<Sigma::CameraFollow*>(GET_CAMERA->GetCurrentCamera())->m_targetP2 = p2;
  }

  
}

} // namespace game
