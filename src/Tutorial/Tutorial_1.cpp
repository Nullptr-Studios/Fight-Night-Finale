#include "Tutorial_1.hpp"
#include "Controller/CameraController.hpp"
#include "Core.hpp"
#include "Factory.hpp"
#include "GameManager.hpp"
#include "Objects/Actor.hpp"
#include "Objects/Camera.hpp"
#include "Objects/CameraFollow.hpp"

// #define DEBUG_CAMERA

namespace game {

void Tutorial1::Load() {
  GameScene::Load();
  background = GET_FACTORY->CreateObject<Sigma::Actor>();
  background->SetTexture("assets/tutorial/tutorial_1.png");
  background->transform.scale = {615.0f, 256.0f};
  background->transform.position.z = -5000;
  AddChild(background);
}

void Tutorial1::Update(double delta) {
  GameScene::Update(delta);
}
void Tutorial1::Free() {
  GameScene::Free();
}
}