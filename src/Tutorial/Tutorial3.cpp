#include "Tutorial3.hpp"
#include "Core.hpp"
#include "Factory.hpp"
#include "Level1/Scene1.hpp"
#include "Objects/Actor.hpp"
#include "Objects/Debug/PunchingBag.hpp"
#include "UI/UIStaticImage.hpp"

namespace game {

void Tutorial3::Load() {
  GameScene::Load();

  background = GET_FACTORY->CreateObject<Sigma::Actor>();
  background->SetTexture("assets/tutorial/tutorial-2.png");
  background->transform.scale = {469.0f, 236.0f};
  background->transform.position.z = -5000;
  AddChild(background);

  m_punchBag = GET_FACTORY->CreateObject<PunchingBag>("Punchbag");
  m_punchBag->transform.position = {0, -75, 75};
  AddChild(m_punchBag);

  m_glowArea = GET_FACTORY->CreateObject<GlowArea>("Glow Area");
  m_glowArea->transform.position = {145, -65, 65};
  AddChild(m_glowArea);

  auto tut = GET_FACTORY->CreateObject<Sigma::StaticImage>("StaticImage");
  tut->SetTexture("assets/tutorial/prompt3.png");
  tut->transform.scale = {320.0f, 180.0f};
  tut->transform.relativeScale = glm::vec2(2);


  AddChild(tut);

  SetNextScene(new Scene1("Level 1", 1, "assets/level-1/scene-1.json"));
}

void Tutorial3::Update(double delta) {
  GameScene::Update(delta);
}

void Tutorial3::Free() {
  GameScene::Free();
}

}

