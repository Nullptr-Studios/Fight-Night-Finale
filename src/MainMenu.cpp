#include "MainMenu.hpp"
#include "Controller/CameraController.hpp"
#include "Core.hpp"
#include "Factory.hpp"
#include "Objects/Camera.hpp"
#include "UI/HealthBar.hpp"
#include "UI/PlayButton.hpp"
#include "UI/QuitButton.hpp"

void game::MainMenu::Load() {
  Scene::Load();
  GET_CAMERA->SetCurrentCamera(GET_FACTORY->CreateObject<Sigma::Camera>("Main Camera"));
  auto playButton = GET_FACTORY->CreateObject<game::PlayButton>("Play Button");
  playButton->transform.scale = {300,100};
  playButton->transform.position.x += 200;
  playButton->SetTexture("assets/UI/PlayButton.png");

  auto quitButton = GET_FACTORY->CreateObject<game::QuitButton>("Quit Button");
  quitButton->transform.scale = {300,100};
  quitButton->transform.position.x -= 200;
  quitButton->SetTexture("assets/UI/ExitButton.png");

  auto progress = GET_FACTORY->CreateObject<game::HealthBar>("Progress");
  progress->m_maxHealth = 100;
  progress->m_currentHealth = 100;
  progress->transform.scale = {400,10};
  progress->transform.position = {0,250,0};
  progress->m_progress = 1;
}
