#include "SceneButton.hpp"
#include "GameManager.hpp"
void game::SceneButton::OnClick() {
  UIButton::OnClick();
  if (m_scene == nullptr) {
    std::cout << "Quiting Game...\n";
    GET_MANAGER->Uninitialize();
    AESysExit();
    return;
  }
  std::cout << "Changing Scene...\n";
  GET_MANAGER->LoadScene(m_scene);
  GET_MANAGER->UnloadScene(m_currentScene);
}
void game::SceneButton::OnHoverStart() {
  UIButton::OnHoverStart();
  transform.scale *= 1.05;
}
void game::SceneButton::OnHoverExit() {
  UIButton::OnHoverExit();
  transform.scale /= 1.05;
}
