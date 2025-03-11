#include "MainMenu.hpp"


#include "Controller/CameraController.hpp"
#include "Objects/Camera.hpp"
#include "Objects/Manager/GameplayManager.hpp"
#include "UI/SceneButton.hpp"
#include "Tutorial/Tutorial3.hpp"

void game::MainMenu::Load() {
  Scene::Load();

  GET_CAMERA->SetCurrentCamera(GET_FACTORY->CreateObject<Sigma::Camera>("Main Camera"));
  

  auto s = new game::Scene1("Game Scene1", 1, "assets/level-1/scene-1.json");
  // auto s = new game::Tutorial2("Tutorial2", 1, "assets/tutorial/tutorial_2.json");
  m_playButton = GET_FACTORY->CreateObject<Sigma::SceneButton>("Play Button", s,GetID());
  m_playButton->m_screenSpaceTransform.scale = {300, 100};
  m_playButton->m_screenSpaceTransform.position.x += 200;
  m_playButton->SetTexture("assets/UI/PlayButton.png");

  AddChild(m_playButton);

  m_quitButton = GET_FACTORY->CreateObject<Sigma::SceneButton>("Quit Button", nullptr,GetID());
  m_quitButton->m_screenSpaceTransform.scale = {300, 100};
  m_quitButton->m_screenSpaceTransform.position.x -= 200; 
  m_quitButton->SetTexture("assets/UI/ExitButton.png");

  AddChild(m_quitButton);

  AddChild(GET_CAMERA->GetCurrentCamera());
 
}
void game::MainMenu::Unload() {
  Scene::Unload();
  GET_FACTORY->CreateObject<game::GameplayManager>("Gameplay Manager");
}
