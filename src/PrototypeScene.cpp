#include "PrototypeScene.hpp"
#include "Core.hpp"
#include "Factory.hpp"
#include "Objects/Actor.hpp"
#include "Player/Player.hpp"
#include "Enemies/Enemy.hpp"

namespace game {

void PrototypeScene::Load() {
  std::cout << "PrototypeScene::Load()" << std::endl;

  auto* floor = GET_FACTORY->CreateObject<Sigma::Actor>("Floor");
  floor->SetTexture("assets/prototype-scene/T_Floors.png");
  floor->transform.scale = {700.0f, 572.0f};
  auto* walls = GET_FACTORY->CreateObject<Sigma::Actor>("Walls");
  walls->SetTexture("assets/prototype-scene/T_Walls.png");
  walls->transform.scale = {700.0f, 572.0f};

  auto p = GET_FACTORY->CreateObject<game::Player>("Player");
  p->SetTexture("assets/prototype-scene/T_Walls.png");
  p->SetJsonPath("assets/characters/dummy.json");

  auto e = GET_FACTORY->CreateObject<game::Enemy>("Enemy");
  e->transform.position = { 400.0f, 0.0f, 0.0f };
  e->SetJsonPath("assets/characters/dummy.json");
}

}
