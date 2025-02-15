//
// Created by Alexey on 15/02/2025.
//

#include "PrototypeScene2.hpp"
#include "Controller/CameraController.hpp"
#include "Core.hpp"
#include "Factory.hpp"
#include "Objects/Actor.hpp"
#include "Objects/Camera.hpp"
#include "Objects/CameraFollow.hpp"

#include "Objects/Destrucibles/Box.hpp"
#include "Objects/Pickups/Pickup.hpp"
#include "Player/Player.hpp"

namespace game {

void PrototypeScene2::Load() {
  GameScene::Load();
  std::cout << "PrototypeScene::Load()" << std::endl;

 GET_CAMERA->SetCurrentCamera(GET_FACTORY->CreateObject<Sigma::CameraFollow>("Main Camera"));
  GET_CAMERA->GetCurrentCamera()->size = 2;

  auto* floor = GET_FACTORY->CreateObject<Sigma::Actor>();
  floor->SetTexture("assets/prototype-scene/T_Floors.png");
  floor->transform.scale = {700.0f, 572.0f};
  floor->transform.position.z = -5000;

  auto* walls = GET_FACTORY->CreateObject<Sigma::Actor>();
  walls->SetTexture("assets/prototype-scene/T_Walls.png");
  walls->transform.scale = {700.0f, 572.0f};
  walls->transform.position.z = -5000;

  auto p = GET_FACTORY->CreateObject<game::Player>("Player", -1, "assets/characters/dummy.json");

  auto Box = GET_FACTORY->CreateObject<game::Box>("Box1");
  Box->SetTexture("assets/prototype-scene-2/Prototype_Box_Default.png");
  Box->transform.scale = {75.0f, 75.0f};
  Box->transform.position.x = 200;

  dynamic_cast<Sigma::CameraFollow*>(GET_CAMERA->GetCurrentCamera())->m_targetP1 = p;

}

}
