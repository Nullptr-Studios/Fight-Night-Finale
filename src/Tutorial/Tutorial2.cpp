#include "Tutorial2.hpp"
#include "Core.hpp"
#include "Factory.hpp"

namespace game {

void Tutorial2::Load() {
  GameScene::Load();

  background = GET_FACTORY->CreateObject<Sigma::Actor>();
  background->SetTexture("assets/tutorial/tutorial_2.png");
  background->transform.scale = {469.0f, 236.0f};
  background->transform.position.z = -5000;
  AddChild(background);
}

void Tutorial2::Update(double delta) {
  GameScene::Update(delta);
}
void Tutorial2::Free() {
  GameScene::Free();
}
}
