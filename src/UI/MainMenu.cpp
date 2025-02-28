#include "MainMenu.hpp"
#include "../../inc/sigma/engine/src/Controller/CameraController.hpp"
#include "../../inc/sigma/engine/src/Core.hpp"
#include "../../inc/sigma/engine/src/Factory.hpp"
#include "../../inc/sigma/engine/src/Objects/Camera.hpp"
#include "../PrototypeScene.hpp"
#include "Level1_Scene.hpp"
#include "UI/SceneButton.hpp"

void game::MainMenu::Load() {
  Scene::Load();

  GET_CAMERA->SetCurrentCamera(GET_FACTORY->CreateObject<Sigma::Camera>("Main Camera"));

  auto s = new game::Level1_Scene("Game Scene", 0, "assets/level-1/scene_2.json");
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
}
