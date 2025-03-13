#include "DeadScene.hpp"
#include "MainMenu.hpp"
#include "Controller/CameraController.hpp"
#include "Level1/Scene1.hpp"
#include "Objects/Camera.hpp"
#include "UI/SceneButton.hpp"

void game::DeadScene::Load() {
  Scene::Load();

  GET_CAMERA->SetCurrentCamera(GET_FACTORY->CreateObject<Sigma::Camera>("Main Camera"));

  m_background = GET_FACTORY->CreateObject<Sigma::Actor>();
  m_background->SetTexture("assets/UI/Sprites/Menu_Background.png");
  m_background->transform.scale = {960.0f, 500.0f};
  m_background->transform.position.z = -5000;

  AddChild(m_background);

  m_death = GET_FACTORY->CreateObject<Sigma::Actor>();
  m_death->SetTexture("assets/UI/Sprites/Death.png");
  m_death->transform.scale = {400.0f, 100.0f};

  AddChild(m_death);

  auto m = new game::MainMenu("Game Scene1", 0);
  m_quitButton = GET_FACTORY->CreateObject<Sigma::SceneButton>("Quit Button", m ,GetID());
  m_quitButton->m_screenSpaceTransform.scale = {200, 100};
  m_quitButton->m_screenSpaceTransform.position.y -= 340;
  m_quitButton->SetTexture("assets/UI/Sprites/Exit_Sign.png");

  AddChild(m_quitButton);

  AddChild(GET_CAMERA->GetCurrentCamera());

}
void game::DeadScene::Unload() {
  Scene::Unload();
}
