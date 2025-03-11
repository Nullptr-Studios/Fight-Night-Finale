#include "MainMenu.hpp"


#include "Controller/CameraController.hpp"
#include "Level1/Scene1.hpp"
#include "Level1/Scene2.hpp"
#include "Objects/Camera.hpp"
#include "Objects/Manager/GameplayManager.hpp"
#include "UI/SceneButton.hpp"

void game::MainMenu::Load() {
  Scene::Load();

  GET_CAMERA->SetCurrentCamera(GET_FACTORY->CreateObject<Sigma::Camera>("Main Camera"));

  m_background = GET_FACTORY->CreateObject<Sigma::Actor>();
  m_background->SetTexture("assets/UI/Sprites/Menu_Background.png");
  m_background->transform.scale = {960.0f, 500.0f};
  m_background->transform.position.z = -5000;

  AddChild(m_background);
  
  auto s = new game::Scene1("Game Scene1", 1, "assets/level-1/scene-1.json");
  m_playButton = GET_FACTORY->CreateObject<Sigma::SceneButton>("Play Button", s, GetID());
  m_playButton->m_screenSpaceTransform.scale = {100, 50};
  m_playButton->m_screenSpaceTransform.position.x -= 360;
  m_playButton->m_screenSpaceTransform.position.y -= 0;
  m_playButton->SetTexture("assets/UI/Sprites/Play_Sign.png");

  AddChild(m_playButton);

  m_controlsButton = GET_FACTORY->CreateObject<Sigma::SceneButton>("Controls Button", nullptr,GetID());
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

  AddChild(m_scoreButton);

  m_quitButton = GET_FACTORY->CreateObject<Sigma::SceneButton>("Quit Button", nullptr,GetID());
  m_quitButton->m_screenSpaceTransform.scale = {100, 50};
  m_quitButton->m_screenSpaceTransform.position.x -= 360;
  m_quitButton->m_screenSpaceTransform.position.y -= 150;
  m_quitButton->SetTexture("assets/UI/Sprites/Exit_Sign.png");

  AddChild(m_quitButton);

  AddChild(GET_CAMERA->GetCurrentCamera());
  
  // auto progress = GET_FACTORY->CreateObject<game::HealthBar>("Progress");
  // progress->m_maxHealth = 100;
  // progress->m_currentHealth = 100;
  // progress->m_isScreenSpaceUI = false;
  // progress->m_screenSpaceTransform.scale = {400, 10};
  // progress->m_screenSpaceTransform.position = {0,250,0};
  // progress->m_progress = 1;

}
void game::MainMenu::Unload() {
  Scene::Unload();
  GET_FACTORY->CreateObject<game::GameplayManager>("Gameplay Manager");
}
