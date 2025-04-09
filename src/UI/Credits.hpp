//
// Created by Xein on 4/9/2025.
//

#pragma once
#include "Scene.hpp"

namespace game {
class Credits final : public Sigma::Scene {
public:
  Credits(const char *name, unsigned ID) : Scene(name, ID) {}
  void Load() override;
  void Update(double delta) override;
  void Unload() override;
private:

  Sigma::Actor *m_credits = nullptr;
  float m_timer;
};
}