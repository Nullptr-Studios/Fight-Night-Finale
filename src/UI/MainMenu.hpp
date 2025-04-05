/**
 * @file MainMenu.hpp
 * @author dante
 * @date 2/13/2025
 *
 * @brief Main Menu
 */
#pragma once
#include "Scene.hpp"
#include "UI/UIText.hpp"
namespace Sigma {
class SceneButton;
class CtrlButton;
}
namespace game {
class MainMenu final : public Sigma::Scene{
public:
  MainMenu(const char *name, unsigned ID) : Scene(name, ID) {}
  void Load() override;
  void Update(double delta) override;
  void Unload() override;
private:
  std::shared_ptr<Sigma::SceneButton> m_playButton = nullptr;
  std::shared_ptr<Sigma::CtrlButton> m_controlsButton = nullptr;
  std::shared_ptr<Sigma::SceneButton> m_scoreButton = nullptr;
  std::shared_ptr<Sigma::SceneButton> m_quitButton = nullptr;
  std::shared_ptr<Sigma::Actor> m_background = nullptr;
  std::shared_ptr<Sigma::Actor> m_logo = nullptr;
  std::shared_ptr<Sigma::Actor> m_studioName = nullptr;
};
}
