#include "MainMenu.hpp"
#include "Controller/CameraController.hpp"
#include "Core.hpp"
#include "Factory.hpp"
#include "Objects/Camera.hpp"
#include "UI/PlayButton.hpp"
#include "UI/QuitButton.hpp"

void game::MainMenu::Load() {
  Scene::Load();
  GET_CAMERA->SetCurrentCamera(GET_FACTORY->CreateObject<Sigma::Camera>("Main Camera"));
  auto playButton = GET_FACTORY->CreateObject<game::PlayButton>("Play Button");
  playButton->transform.position.x += 200;
  
  auto quitButton = GET_FACTORY->CreateObject<game::QuitButton>("Quit Button");
  quitButton->transform.position.x -= 200;
}
