/**
 * @file DeadMenu.hpp
 * @author dante
 * @date 2/16/2025
 *
 * @brief dead screen
 */
#pragma once
#include "Scene.hpp"
namespace Sigma {
class UIElement;
class SceneButton;
}
namespace game {
class DeadMenu final : public Sigma::Scene {
public:
  DeadMenu(const char *name, unsigned ID) : Scene(name, ID) {}
  void Load() override;
  void Unload() override;
private:
  Sigma::UIElement * m_background{};
  Sigma::SceneButton * m_button{};
};
}