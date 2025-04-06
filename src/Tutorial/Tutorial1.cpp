#include "Tutorial1.hpp"
#include "Core.hpp"
#include "Factory.hpp"
#include "Objects/Actor.hpp"
#include "Tutorial/GlowArea.hpp"
#include "Tutorial/Tutorial2.hpp"
#include "UI/UIStaticImage.hpp"

//Debugging purposes
#include "Level1/Scene1.hpp"
#include "Level1/Scene2.hpp"
#include "Level1/Scene3.hpp"
#include "Level1/Scene4.hpp"
#include "Level1/Scene5.hpp"
#include "Level1/Scene6.hpp"
#include "Level1/Scene7.hpp"
#include "Level1/Scene8.hpp"
#include "Level1/Scene9.hpp"

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
  //SetNextScene(new Scene9("Game Scene 9", 9, "assets/level-1/scene-9.json"));

  auto tut = GET_FACTORY->CreateObject<Sigma::StaticImage>("StaticImage");
  tut->SetTexture("assets/tutorial/prompt1.png");
  tut->transform.scale = {320.0f, 180.0f};
  tut->transform.relativeScale = glm::vec2(2);

  /*auto tut2 = GET_FACTORY->CreateObject<Sigma::Actor>();
  tut2->SetTexture("assets/tutorial/SpawnPrompt.png");
  tut2->transform.scale = {256.0f, 16.0f};
  tut2->transform.position.y = -160;

  AddChild(tut2);*/

  GameplayManager::GetInstance()->StartGame();
}

void Tutorial1::Update(double delta) {
  GameScene::Update(delta);
}
void Tutorial1::Free() {
  GameScene::Free();
}

}

