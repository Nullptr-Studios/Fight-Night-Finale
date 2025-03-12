#include "MainMenu.hpp"


#include "Controller/CameraController.hpp"
#include "Level1/Scene1.hpp"
#include "Objects/Camera.hpp"
#include "Objects/Manager/GameplayManager.hpp"
#include "Tutorial/Tutorial1.hpp"
#include "Tutorial/Tutorial2.hpp"
#include "Tutorial/Tutorial3.hpp"
#include "UI/SceneButton.hpp"
#include "UI/ControlButton.hpp"
#include "DeadScene.hpp"
#include "WinScene.hpp"

void game::MainMenu::Load() {
  Scene::Load();

  GET_CAMERA->SetCurrentCamera(GET_FACTORY->CreateObject<Sigma::Camera>("Main Camera"));

  m_background = GET_FACTORY->CreateObject<Sigma::Actor>();
  m_background->SetTexture("assets/UI/Sprites/Menu_Background.png");
  m_background->transform.scale = {960.0f, 500.0f};
  m_background->transform.position.z = -5000;

  AddChild(m_background);

  m_logo = GET_FACTORY->CreateObject<Sigma::Actor>();
  m_logo->SetTexture("assets/UI/Sprites/Untitled.png");
  m_logo->transform.scale = {500, 500.0f};
  m_logo->transform.position.y = 60;

  AddChild(m_logo);
  
  auto s = new game::Tutorial1("Tutorial 1 ", 1, "assets/tutorial/tutorial-1.json");
  //auto d = new game::WinScene("Game Scene1", 0);
  m_playButton = GET_FACTORY->CreateObject<Sigma::SceneButton>("Play Button", s, GetID());
  m_playButton->m_screenSpaceTransform.scale = {100, 50};
  m_playButton->m_screenSpaceTransform.position.x -= 360;
  m_playButton->m_screenSpaceTransform.position.y -= 0;
  m_playButton->SetTexture("assets/UI/Sprites/Play_Sign.png");

  AddChild(m_playButton);

  m_controlsButton = GET_FACTORY->CreateObject<Sigma::CtrlButton>("Controls Button");
  m_controlsButton->m_screenSpaceTransform.scale = {175, 50};
  m_controlsButton->m_screenSpaceTransform.position.x -= 360;
  m_controlsButton->m_screenSpaceTransform.position.y -= 50;
  m_controlsButton->SetTexture("assets/UI/Sprites/Controls.png");

  AddChild(m_controlsButton);

  m_scoreButton = GET_FACTORY->CreateObject<Sigma::SceneButton>("Score Button", nullptr,GetID());
  m_scoreButton->m_screenSpaceTransform.scale = {100, 50};
  m_scoreButton->m_screenSpaceTransform.position.x -= 360;
  m_scoreButton->m_screenSpaceTransform.position.y -= 100;
  m_scoreButton->SetTexture("assets/UI/Sprites/Score.png");
  m_scoreButton->SetTint({.5,.5,.5,1});
  m_scoreButton->DisableUpdate();

  AddChild(m_scoreButton);

  m_quitButton = GET_FACTORY->CreateObject<Sigma::SceneButton>("Quit Button", nullptr,GetID());
  m_quitButton->m_screenSpaceTransform.scale = {100, 50};
  m_quitButton->m_screenSpaceTransform.position.x -= 360;
  m_quitButton->m_screenSpaceTransform.position.y -= 150;
  m_quitButton->SetTexture("assets/UI/Sprites/Exit_Sign.png");

  AddChild(m_quitButton);

  AddChild(GET_CAMERA->GetCurrentCamera());
 
}
void game::MainMenu::Unload() {
  Scene::Unload();
  if (GameplayManager::GetInstance() == nullptr)
    GET_FACTORY->CreateObject<game::GameplayManager>("Gameplay Manager");
}
