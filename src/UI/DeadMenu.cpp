#include "DeadMenu.hpp"
#include "Controller/CameraController.hpp"
#include "Factory.hpp"
#include "Objects/Camera.hpp"
#include "UI/SceneButton.hpp"
#include "core.hpp"

namespace Sigma {
class SceneButton;
}
namespace game {

void DeadMenu::Load() {
  Scene::Load();
  GET_CAMERA->SetCurrentCamera(GET_FACTORY->CreateObject<Sigma::Camera>("Main Camera"));

  auto menu = GET_FACTORY->CreateObject<Sigma::UIElement>();
  menu->transform.scale = {960, 720};
  menu->SetTexture("assets/UI/Died.png");

  auto quitButton = GET_FACTORY->CreateObject<Sigma::SceneButton>("Quit Button", nullptr,GetID());
  quitButton->m_screenSpaceTransform.scale = {300, 100};
  quitButton->transform.position.y -= 200;
  quitButton->SetTexture("assets/UI/ExitButton.png");
}
void DeadMenu::Unload() {
  Scene::Unload();
  GET_FACTORY->DestroyObject(m_background->GetId());
  GET_FACTORY->DestroyObject(m_button->GetId());
}
} // namespace game
