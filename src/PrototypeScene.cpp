#include "PrototypeScene.hpp"
#include "Core.hpp"
#include "Factory.hpp"
#include "Objects/Actor.hpp"

#include "Objects/Debug/PunchingBag.hpp"
#include "Player/Player.hpp"

namespace game {

void PrototypeScene::Load() {
  GameScene::Load();
  std::cout << "PrototypeScene::Load()" << std::endl;

  

  auto* floor = GET_FACTORY->CreateObject<Sigma::Actor>();
  floor->SetTexture("assets/prototype-scene/T_Floors.png");
  floor->transform.scale = {700.0f, 572.0f};
  floor->transform.position.z = -1000;
  
  auto* walls = GET_FACTORY->CreateObject<Sigma::Actor>();
  walls->SetTexture("assets/prototype-scene/T_Walls.png");
  walls->transform.scale = {700.0f, 572.0f};
  walls->transform.position.z = -1000;
  
  auto p = GET_FACTORY->CreateObject<game::Player>("Player", -1);

  auto b = GET_FACTORY->CreateObject<game::PunchingBag>();
  
  //p->SetTexture("assets/prototype-scene/T_Walls.png");
  //b->m_animComp->AddCallback("test", []() { std::cout << "Callback\n"; });
  

}

}
