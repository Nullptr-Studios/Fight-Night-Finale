#include "HUD.hpp"
#include "Core.hpp"
#include "Factory.hpp"
#include "Objects/Manager/GameplayManager.hpp"
#include "Player/Player.hpp"
#include "UI/UIImage.hpp"
#include "UI/UINumber.hpp"
#include "UI/HealthBar.hpp"
#include "UI/UIText.hpp"

namespace game {

void HUD::Init() {
#pragma region Player1
  player1.offset = {-280, 190, 0};

  player1.background = GET_FACTORY->CreateObject<Sigma::UIImage>("Healthbar Background", "HealthbarBackground");
  player1.background->m_screenSpaceTransform.scale = {107, 10};
  player1.background->m_screenSpaceTransform.scale *= 2.0f;
  player1.background->m_screenSpaceTransform.position = player1.offset;
  player1.blue = GET_FACTORY->CreateObject<HealthBar>("Healthbar Blue", "HealthbarBlue");
  player1.blue->SetScale({214, 20});
  player1.blue->m_screenSpaceTransform.position = player1.offset;
  player1.blue->m_screenSpaceTransform.position.x += -107;
  player1.blue->m_screenSpaceTransform.position.y += 8;
  player1.blue->SetAlignment(Sigma::UIProgressBar::LEFT);
  player1.health = GET_FACTORY->CreateObject<HealthBar>("Healthbar Red", "HealthbarRed");
  player1.health->SetScale({214, 20});
  player1.health->m_screenSpaceTransform.position = player1.offset;
  player1.health->m_screenSpaceTransform.position.x += -107;
  player1.health->m_screenSpaceTransform.position.y += 8;
  player1.health->SetAlignment(Sigma::UIProgressBar::LEFT);
  player1.border = GET_FACTORY->CreateObject<Sigma::UIImage>("Healthbar Border", "HealthbarRim");
  player1.border->m_screenSpaceTransform.position = player1.offset;
  player1.border->m_screenSpaceTransform.scale = {109, 12};
  player1.border->m_screenSpaceTransform.scale *= 2.0f;
  player1.border->m_screenSpaceTransform.position.y += -2.0f;

  player1.frame = GET_FACTORY->CreateObject<Sigma::UIImage>("Frame", "PlaceholderFrame");
  player1.frame->m_screenSpaceTransform.position = player1.offset;
  player1.frame->m_screenSpaceTransform.scale = {28, 24};
  player1.frame->m_screenSpaceTransform.scale *= 2.0f;
  player1.frame->m_screenSpaceTransform.position.x += -140.0f;
  player1.frame->m_screenSpaceTransform.position.y += -6.0f;

  player1.currentHealth[0] = GET_FACTORY->CreateObject<Sigma::UINumber>("CurrentHealth Decs");
  player1.currentHealth[0]->m_screenSpaceTransform.position = player1.offset;
  player1.currentHealth[0]->m_screenSpaceTransform.scale = {18, 21};
  player1.currentHealth[0]->m_screenSpaceTransform.position.x += -100;
  player1.currentHealth[0]->m_screenSpaceTransform.position.y += 22;
  player1.currentHealth[1] = GET_FACTORY->CreateObject<Sigma::UINumber>("CurrentHealth Units");
  player1.currentHealth[1]->m_screenSpaceTransform.position = player1.offset;
  player1.currentHealth[1]->m_screenSpaceTransform.scale = {18, 21};
  player1.currentHealth[1]->m_screenSpaceTransform.position.x += -80;
  player1.currentHealth[1]->m_screenSpaceTransform.position.y += 22;

  player1.slash = GET_FACTORY->CreateObject<Sigma::UIText>("Slash");
  player1.slash->m_screenSpaceTransform.position = player1.offset;
  player1.slash->m_screenSpaceTransform.scale = {0.5f, 0.9f};
  player1.slash->m_screenSpaceTransform.position.x += -68;
  player1.slash->m_screenSpaceTransform.position.y += 24;
  player1.slash->SetText("/");
  player1.slash->SetTint({1.0f, 1.0f, 1.0f, 1.0f});

  player1.maxHealth[0] = GET_FACTORY->CreateObject<Sigma::UINumber>("MaxHealth Decs");
  player1.maxHealth[0]->m_screenSpaceTransform.position = player1.offset;
  player1.maxHealth[0]->m_screenSpaceTransform.scale = {12, 14};
  player1.maxHealth[0]->m_screenSpaceTransform.position.x += -52;
  player1.maxHealth[0]->m_screenSpaceTransform.position.y += 18;
  player1.maxHealth[1] = GET_FACTORY->CreateObject<Sigma::UINumber>("MaxHealth Units");
  player1.maxHealth[1]->m_screenSpaceTransform.position = player1.offset;
  player1.maxHealth[1]->m_screenSpaceTransform.scale = {12, 14};
  player1.maxHealth[1]->m_screenSpaceTransform.position.x += -39;
  player1.maxHealth[1]->m_screenSpaceTransform.position.y +=  18;
#pragma endregion

#pragma region Player2
  player2.offset = {280, 190, 0};

  player2.background = GET_FACTORY->CreateObject<Sigma::UIImage>("Healthbar Background", "HealthbarBackground");
  player2.background->m_screenSpaceTransform.scale = { 107, 10 };
  player2.background->m_screenSpaceTransform.scale *= 2.0f;
  player2.background->m_screenSpaceTransform.position = player2.offset;
  player2.blue = GET_FACTORY->CreateObject<HealthBar>("Healthbar Blue", "HealthbarBlue");
  player2.blue->SetScale({214, 20 });
  player2.blue->m_screenSpaceTransform.position = player2.offset;
  player2.blue->m_screenSpaceTransform.position.x +=  107;
  player2.blue->m_screenSpaceTransform.position.y +=    8;
  player2.blue->SetAlignment(Sigma::UIProgressBar::RIGHT);
  player2.health = GET_FACTORY->CreateObject<HealthBar>("Healthbar Red", "HealthbarRed");
  player2.health->SetScale({ 214, 20 });
  player2.health->m_screenSpaceTransform.position = player2.offset;
  player2.health->m_screenSpaceTransform.position.x +=  107;
  player2.health->m_screenSpaceTransform.position.y +=    8;
  player2.health->SetAlignment(Sigma::UIProgressBar::RIGHT);
  player2.border = GET_FACTORY->CreateObject<Sigma::UIImage>("Healthbar Border", "HealthbarRim");
  player2.border->m_screenSpaceTransform.position = player2.offset;
  player2.border->m_screenSpaceTransform.scale = { 109, 12 };
  player2.border->m_screenSpaceTransform.scale *= 2.0f;
  player2.border->m_screenSpaceTransform.position.y +=  -2.0f;

  player2.frame = GET_FACTORY->CreateObject<Sigma::UIImage>("Frame", "PlaceholderFrame");
  player2.frame->m_screenSpaceTransform.position = player2.offset;
  player2.frame->m_screenSpaceTransform.scale = { 28, 24 };
  player2.frame->m_screenSpaceTransform.scale *= 2.0f;
  player2.frame->m_screenSpaceTransform.position.x +=  140.0f;
  player2.frame->m_screenSpaceTransform.position.y += -6.0f;

  player2.currentHealth[0] = GET_FACTORY->CreateObject<Sigma::UINumber>("CurrentHealth Decs");
  player2.currentHealth[0]->m_screenSpaceTransform.position = player2.offset;
  player2.currentHealth[0]->m_screenSpaceTransform.scale = { 18, 21 };
  player2.currentHealth[0]->m_screenSpaceTransform.position.x +=  40;
  player2.currentHealth[0]->m_screenSpaceTransform.position.y +=  22;
  player2.currentHealth[1] = GET_FACTORY->CreateObject<Sigma::UINumber>("CurrentHealth Units");
  player2.currentHealth[1]->m_screenSpaceTransform.position = player2.offset;
  player2.currentHealth[1]->m_screenSpaceTransform.scale = { 18, 21 };
  player2.currentHealth[1]->m_screenSpaceTransform.position.x +=  60;
  player2.currentHealth[1]->m_screenSpaceTransform.position.y +=  22;

  player2.slash = GET_FACTORY->CreateObject<Sigma::UIText>("Slash");
  player2.slash->m_screenSpaceTransform.position = player2.offset;
  player2.slash->m_screenSpaceTransform.scale = {0.5f, 0.9f};
  player2.slash->m_screenSpaceTransform.position.x +=  71;
  player2.slash->m_screenSpaceTransform.position.y +=  24;
  player2.slash->SetText("/");
  player2.slash->SetTint({1.0f, 1.0f, 1.0f, 1.0f});

  player2.maxHealth[0] = GET_FACTORY->CreateObject<Sigma::UINumber>("MaxHealth Decs");
  player2.maxHealth[0]->m_screenSpaceTransform.position = player2.offset;
  player2.maxHealth[0]->m_screenSpaceTransform.scale = { 12, 14 };
  player2.maxHealth[0]->m_screenSpaceTransform.position.x +=  87;
  player2.maxHealth[0]->m_screenSpaceTransform.position.y +=  18;
  player2.maxHealth[1] = GET_FACTORY->CreateObject<Sigma::UINumber>("MaxHealth Units");
  player2.maxHealth[1]->m_screenSpaceTransform.position = player2.offset;
  player2.maxHealth[1]->m_screenSpaceTransform.scale = { 12, 14 };
  player2.maxHealth[1]->m_screenSpaceTransform.position.x += 100;
  player2.maxHealth[1]->m_screenSpaceTransform.position.y +=  18;
#pragma endregion
}

void HUD::Start() {}

void HUD::UpdatePlayerHUD() {
  m_players = GameplayManager::GetInstance()->GetPlayers();
  SetNumbers(player1.maxHealth, std::floor(m_players->operator[](0).player->GetMaxHealth()));
  SetNumbers(player1.currentHealth, std::floor(m_players->operator[](0).player->GetHealth()));
  player1.health->m_maxHealth = m_players->operator[](0).player->GetMaxHealth();
  player1.health->m_currentHealth = m_players->operator[](0).player->GetHealth();
  player1.blue->m_maxHealth = m_players->operator[](0).player->GetMaxHealth();
  player1.blue->m_currentHealth = m_players->operator[](0).player->GetHealth();

  m_players->operator[](0).player->healthBar = &player1;


  if (m_players->at(1).player != nullptr) {
    SetNumbers(player2.maxHealth, std::floor(m_players->operator[](1).player->GetMaxHealth()));
    SetNumbers(player2.currentHealth, std::floor(m_players->operator[](1).player->GetHealth()));
    player2.health->m_maxHealth = m_players->operator[](1).player->GetMaxHealth();
    player2.health->m_currentHealth = m_players->operator[](1).player->GetHealth();
    player2.blue->m_maxHealth = m_players->operator[](1).player->GetMaxHealth();
    player2.blue->m_currentHealth = m_players->operator[](1).player->GetHealth();

    m_players->operator[](1).player->healthBar = &player2;
  }
}

void HUD::Update(double delta) {}

void HUD::SetNumbers(std::array<Sigma::UINumber *, 2> numbers, int value) {
  value = glm::clamp(value, 0, 99);
  numbers[0]->Change(value / 10);
  numbers[1]->Change(value % 10);
}

void HUD::SetPlayer1Health(int health) {}

} // namespace game
