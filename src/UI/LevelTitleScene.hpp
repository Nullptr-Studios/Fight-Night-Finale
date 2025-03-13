//
// Created by Dario on 12/03/2025.
//

#pragma once

#include "Scene.hpp"
#include "UI/UIImage.hpp"

namespace Sigma {
class UIText;
}
class LevelTitleScene : public Sigma::Scene {
  
public:
  LevelTitleScene(const char *name, unsigned ID) : Scene(name, ID) {};
  
  void Load() override;
  void Unload() override;
  void Update(double delta) override;
  void DebugWindow() override;

private:
  Sigma::UIText *m_title = nullptr;
  Sigma::UIImage *m_background = nullptr;

};


