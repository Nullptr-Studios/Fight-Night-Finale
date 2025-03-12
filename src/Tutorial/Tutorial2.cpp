#include "Tutorial2.hpp"
#include "Core.hpp"
#include "Factory.hpp"
#include "GlowArea.hpp"
#include "Objects/Destructibles/Box.hpp"
#include "Tutorial/Tutorial3.hpp"

namespace game {

void Tutorial2::Load() {
  GameScene::Load();


  background = GET_FACTORY->CreateObject<Sigma::Actor>("Floor");
  background->SetTexture("assets/tutorial/tutorial-2.png");
  background->transform.scale = {469.0f, 236.0f};
  background->transform.position.z = -5000;
  AddChild(background);

  m_glowArea = GET_FACTORY->CreateObject<GlowArea>("Glow area");
  m_glowArea->transform.position = {128, -64, 64};
  AddChild(m_glowArea);

  auto box = GET_FACTORY->CreateObject<game::Box>("Box");
  box->transform.position = {0, -64, 64};
  AddChild(box);

  SetNextScene(new Tutorial3("Tutorial 3", 2, "assets/tutorial/tutorial-3.json"));
}

void Tutorial2::Update(double delta) {
  GameScene::Update(delta);
}
void Tutorial2::Free() {
  GameScene::Free();
}
}
