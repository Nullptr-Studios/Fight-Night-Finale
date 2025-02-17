/**
 * @file MainMenu.hpp
 * @author dante
 * @date 2/13/2025
 *
 * @brief Main Menu
 */
#pragma once
#include "Scene.hpp"
namespace game {
class SceneButton;
}
namespace game {
class MainMenu final : public Sigma::Scene{
public:
  MainMenu(const char *name, unsigned ID) : Scene(name, ID) {}
  void Load() override;
  void Unload() override;
private:
  SceneButton * m_playButton;
  SceneButton * m_quitButton;
};
}
