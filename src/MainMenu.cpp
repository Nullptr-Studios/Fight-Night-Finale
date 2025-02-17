#include "MainMenu.hpp"
#include "Controller/CameraController.hpp"
#include "Core.hpp"
#include "Factory.hpp"
#include "Objects/Camera.hpp"
#include "PrototypeScene.hpp"
#include "UI/HealthBar.hpp"
#include "UI/SceneButton.hpp"

void game::MainMenu::Load() {
  Scene::Load();

  GET_CAMERA->SetCurrentCamera(GET_FACTORY->CreateObject<Sigma::Camera>("Main Camera"));

  auto s = new game::PrototypeScene("Game Scene", 0, "assets/prototype-scene-2/ProtoScene2.json");
  m_playButton = GET_FACTORY->CreateObject<game::SceneButton>("Play Button", s,GetID());
  m_playButton->transform.scale = {300, 100};
  m_playButton->transform.position.x += 200;
  m_playButton->SetTexture("assets/UI/PlayButton.png");

  m_quitButton = GET_FACTORY->CreateObject<game::SceneButton>("Quit Button", nullptr,GetID());
  m_quitButton->transform.scale = {300, 100};
  m_quitButton->transform.position.x -= 200;
  m_quitButton->SetTexture("assets/UI/ExitButton.png");

  // auto progress = GET_FACTORY->CreateObject<game::HealthBar>("Progress");
  // progress->m_maxHealth = 100;
  // progress->m_currentHealth = 100;
  // progress->transform.scale = {400, 10};
  // progress->transform.position = {0, 250, 0};
  // progress->m_progress = 1;
}
void game::MainMenu::Unload() {
  Scene::Unload();
  GET_FACTORY->DestroyObject(m_playButton);
  GET_FACTORY->DestroyObject(m_quitButton);
}
