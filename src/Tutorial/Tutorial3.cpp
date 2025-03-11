#include "Tutorial3.hpp"
#include "Core.hpp"
#include "Factory.hpp"
#include "Objects/Actor.hpp"

namespace game {

void Tutorial3::Load() {
  GameScene::Load();

  background = GET_FACTORY->CreateObject<Sigma::Actor>();
  background->SetTexture("assets/tutorial/tutorial_2.png");
  background->transform.scale = {469.0f, 236.0f};
  background->transform.position.z = -5000;
  AddChild(background);
}

void Tutorial3::Update(double delta) {
  GameScene::Update(delta);
}
void Tutorial3::Free() {
  GameScene::Free();
}
}

