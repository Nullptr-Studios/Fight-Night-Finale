#include "Tutorial2.hpp"
#include "Core.hpp"
#include "Factory.hpp"
#include "GlowArea.hpp"
#include "Tutorial/Tutorial3.hpp"

namespace game {

void Tutorial2::Load() {
  GameScene::Load();

  SetNextScene(new Tutorial3("Tutorial3", 5, "assets/tutorial/tutorial-3.json"));

  background = GET_FACTORY->CreateObject<Sigma::Actor>("Floor");
  background->SetTexture("assets/tutorial/tutorial-2.png");
  background->transform.scale = {469.0f, 236.0f};
  background->transform.position.z = -5000;
  AddChild(background);

  m_glowArea = GET_FACTORY->CreateObject<GlowArea>("Glow area");
  m_glowArea->transform.position = {128, -64, 64};
  AddChild(m_glowArea);
}

void Tutorial2::Update(double delta) {
  GameScene::Update(delta);
}
void Tutorial2::Free() {
  GameScene::Free();
}
}
