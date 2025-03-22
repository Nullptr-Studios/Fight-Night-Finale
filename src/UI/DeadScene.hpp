/**
* @file DeadScene.hpp
 * @author Alexey
 * @date 3/12/2025
 * @brief Dead Scene
 */
#pragma once
#include "Scene.hpp"
namespace Sigma {
class SceneButton;
}
namespace game {
class DeadScene final : public Sigma::Scene{
public:
  DeadScene(const char *name, unsigned ID) : Scene(name, ID) {}
  void Load() override;
  void Unload() override;
private:
  std::shared_ptr<Sigma::SceneButton> m_quitButton = nullptr;
  std::shared_ptr<Sigma::Actor> m_background = nullptr;
  std::shared_ptr<Sigma::Actor> m_death = nullptr;
};
}
