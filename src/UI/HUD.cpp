#include "HUD.hpp"
#include "Core.hpp"
#include "Factory.hpp"
#include "UI/UIImage.hpp"
#include "UI/UINumber.hpp"
#include "UI/UIText.hpp"
#include "Player/Player.hpp"
#include "UI/UIProgressBar.hpp"

namespace game {

void HUD::Init() {
  player1.background = GET_FACTORY->CreateObject<Sigma::UIImage>("Healthbar Background", "HealthbarBackground");
  player1.background->m_screenSpaceTransform.scale = { 107, 10 };
  player1.background->m_screenSpaceTransform.scale *= 4.0f;
  player1.blue = GET_FACTORY->CreateObject<HealthBar>("Healthbar Blue", "HealthbarBlue");
  player1.blue->SetScale({107, 10 });
  player1.blue->m_screenSpaceTransform.scale *= 4.0f;
  player1.health = GET_FACTORY->CreateObject<HealthBar>("Healthbar Red", "HealthbarRed");
  player1.health->SetScale({ 107, 10 });
  player1.health->m_screenSpaceTransform.scale *= 4.0f;
  player1.border = GET_FACTORY->CreateObject<Sigma::UIImage>("Healthbar Border", "HealthbarRim");
  player1.border->m_screenSpaceTransform.scale = { 109, 12 };
  player1.border->m_screenSpaceTransform.scale *= 4.0f;
  player1.border->m_screenSpaceTransform.position.y +=  -7.0f;

  player1.frame = GET_FACTORY->CreateObject<Sigma::UIImage>("Frame", "PlaceholderFrame");
  player1.frame->m_screenSpaceTransform.scale = { 28, 24 };
  player1.frame->m_screenSpaceTransform.scale *= 4.0f;
  player1.frame->m_screenSpaceTransform.position.x += -280.0f;
  player1.frame->m_screenSpaceTransform.position.y += -28.8f;

  player1.currentHealth[0] = GET_FACTORY->CreateObject<Sigma::UINumber>("CurrentHealth Decs");
  player1.currentHealth[0]->m_screenSpaceTransform.scale = { 36, 42 };
  player1.currentHealth[0]->m_screenSpaceTransform.position.x += -192;
  player1.currentHealth[0]->m_screenSpaceTransform.position.y +=   36;
  player1.currentHealth[1] = GET_FACTORY->CreateObject<Sigma::UINumber>("CurrentHealth Units");
  player1.currentHealth[1]->m_screenSpaceTransform.scale = { 36, 42 };
  player1.currentHealth[1]->m_screenSpaceTransform.position.x += -152;
  player1.currentHealth[1]->m_screenSpaceTransform.position.y +=   36;

  player1.slash = GET_FACTORY->CreateObject<Sigma::UIText>("Slash");
  player1.slash->m_screenSpaceTransform.scale = {1, 1.8f};
  player1.slash->m_screenSpaceTransform.position.x += -130;
  player1.slash->m_screenSpaceTransform.position.y +=   54;
  player1.slash->SetText("/");
  player1.slash->SetTint({1.0f, 1.0f, 1.0f, 1.0f});

  player1.maxHealth[0] = GET_FACTORY->CreateObject<Sigma::UINumber>("MaxHealth Decs");
  player1.maxHealth[0]->m_screenSpaceTransform.scale = { 24, 28 };
  player1.maxHealth[0]->m_screenSpaceTransform.position.x += -97;
  player1.maxHealth[0]->m_screenSpaceTransform.position.y +=  30;
  player1.maxHealth[1] = GET_FACTORY->CreateObject<Sigma::UINumber>("MaxHealth Units");
  player1.maxHealth[1]->m_screenSpaceTransform.scale = { 24, 28 };
  player1.maxHealth[1]->m_screenSpaceTransform.position.x += -71;
  player1.maxHealth[1]->m_screenSpaceTransform.position.y +=  30;
}

void HUD::Start() {
  // FIXME
  /*m_players[0]->healthBar = this;
  SetNumbers(player1.maxHealth, std::floor(m_players[0]->GetMaxHealth()));
  SetNumbers(player1.currentHealth, std::floor(m_players[0]->GetHealth()));*/
}

void HUD::Update(double delta) {

}

void HUD::SetNumbers(std::array<Sigma::UINumber*, 2> numbers, int value) {
  value = glm::clamp(value, 0, 99);

  numbers[0]->Change(value/10);
  numbers[1]->Change(value%10);
}

void HUD::SetPlayer1Health(int health) {
  // FIXME
  //SetNumbers(player1.currentHealth, health);
}

}

