#include "DeadMenu.hpp"

#include "Controller/CameraController.hpp"
#include "Factory.hpp"
#include "Objects/Camera.hpp"
#include "QuitButton.hpp"
#include "core.hpp"

namespace game {

void DeadMenu::Load() {
  Scene::Load();
  GET_CAMERA->SetCurrentCamera(GET_FACTORY->CreateObject<Sigma::Camera>("Main Camera"));
  
  auto menu = GET_FACTORY->CreateObject<Sigma::UIImage>();
  menu->transform.scale = {960, 720};
  menu->SetTexture("assets/UI/Died.png");
  
  auto quitButton = GET_FACTORY->CreateObject<game::QuitButton>("Quit Button");
  quitButton->transform.scale = {300,100};
  quitButton->transform.position.y -= 200;
  quitButton->SetTexture("assets/UI/ExitButton.png");


}
} // namespace game
