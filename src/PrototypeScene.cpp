#include "PrototypeScene.hpp"
#include "Core.hpp"
#include "Factory.hpp"
#include "Objects/Actor.hpp"
#include "Player/Player.hpp"

namespace game {

void PrototypeScene::Load() {
  std::cout << "PrototypeScene::Load()" << std::endl;

  auto* floor = GET_FACTORY->CreateObject<Sigma::Actor>();
  floor->SetTexture("assets/prototype-scene/T_Floors.png");
  floor->transform.scale = {700.0f, 572.0f};
  auto* walls = GET_FACTORY->CreateObject<Sigma::Actor>();
  walls->SetTexture("assets/prototype-scene/T_Walls.png");
  walls->transform.scale = {700.0f, 572.0f};

  auto p = GET_FACTORY->CreateObject<game::Player>();
  p->SetTexture("assets/prototype-scene/T_Walls.png");
  p->SetJsonPath("assets/characters/dummy.json");


}

}
