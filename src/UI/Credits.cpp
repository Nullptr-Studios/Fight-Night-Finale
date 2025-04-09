//
// Created by Xein on 4/9/2025.
//

#include "Objects/Actor.hpp"
#include "Credits.hpp"
#include "GameManager.hpp"
#include "MainMenu.hpp"

namespace game {
void Credits::Load() {
  m_credits = GET_FACTORY->CreateObject<Sigma::Actor>("Credits");
  m_credits->SetTexture("assets/credits.png");
  // Oh wow i love magic numbers 0x
  m_credits->transform.scale = { 2667/(1.39f*2.8), 10500/(1.39f*2.8)};
  m_credits->transform.position.y -= m_credits->transform.scale.y / 2 - 180;
  AddChild(m_credits);

  m_timer = 0;
}

void Credits::Update(double delta) {
  m_timer += delta;
  // Initial wait
  if (m_timer < 5) return;

  // Exit credits
  if (m_timer > 55.5f) {
    auto s = new game::MainMenu("Main Menu", 0);
    GET_MANAGER->UnloadScene(GetID());
    GET_MANAGER->LoadScene(s);
    
  }

  // Second wait
  if (m_timer > 50.5f) return;

  // Move credits
  m_credits->transform.position.y += delta * 200/(1.39f*2.8);
}

void Credits::Unload() { }


}