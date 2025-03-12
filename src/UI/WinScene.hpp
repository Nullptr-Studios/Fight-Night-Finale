/**
* @file WinScene.hpp
 * @author Alexey
 * @date 3/12/2025
 * @brief Win Scene
 */
#pragma once
#include "Scene.hpp"
namespace Sigma {
class SceneButton;
}
namespace game {
class WinScene final : public Sigma::Scene{
public:
  WinScene(const char *name, unsigned ID) : Scene(name, ID) {}
  void Load() override;
  void Unload() override;
private:
  Sigma::SceneButton *m_quitButton = nullptr;
  Sigma::Actor *m_background = nullptr;
  Sigma::Actor *m_death = nullptr;
};
}