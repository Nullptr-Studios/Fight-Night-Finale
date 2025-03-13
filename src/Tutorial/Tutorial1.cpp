#include "Tutorial1.hpp"
#include "Core.hpp"
#include "Factory.hpp"
#include "Objects/Actor.hpp"
#include "Tutorial/GlowArea.hpp"
#include "Tutorial/Tutorial2.hpp"
#include "UI/UIStaticImage.hpp"

namespace game {

void Tutorial1::Load() {
  GameScene::Load();

  

  m_background = GET_FACTORY->CreateObject<Sigma::Actor>();
  m_background->SetTexture("assets/tutorial/tutorial-1.png");
  m_background->transform.scale = {615.0f, 256.0f};
  m_background->transform.position.z = -5000;
  AddChild(m_background);

  m_glowArea = GET_FACTORY->CreateObject<GlowArea>("Glow area");
  m_glowArea->transform.position = {229, -99, 99};
  AddChild(m_glowArea);

  SetNextScene(new Tutorial2("Tutorial 2", 1, "assets/tutorial/tutorial-2.json"));

  auto tut = GET_FACTORY->CreateObject<Sigma::StaticImage>("StaticImage");
  tut->SetTexture("assets/tutorial/prompt1.png");
  tut->transform.scale = {320.0f, 180.0f};
  tut->transform.relativeScale = glm::vec2(2);

  GameplayManager::GetInstance()->StartGame();
}

void Tutorial1::Update(double delta) {
  GameScene::Update(delta);
}
void Tutorial1::Free() {
  GameScene::Free();
}

}

