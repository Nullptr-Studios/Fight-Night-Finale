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
  player1.offset = {-600, 420, 0};

  player1.background = GET_FACTORY->CreateObject<Sigma::UIImage>("Healthbar Background", "HealthbarBackground");
  player1.background->m_screenSpaceTransform.scale = { 424, 40 };
  player1.background->m_screenSpaceTransform.position = player1.offset;
  player1.blue = GET_FACTORY->CreateObject<HealthBar>("Healthbar Blue", "HealthbarBlue");
  player1.blue->SetScale({424, 40 });
  player1.blue->m_screenSpaceTransform.position = player1.offset;
  player1.blue->m_screenSpaceTransform.position.x += -212;
  player1.blue->SetAlignment(Sigma::UIProgressBar::LEFT);
  player1.health = GET_FACTORY->CreateObject<HealthBar>("Healthbar Red", "HealthbarRed");
  player1.health->SetScale({ 424, 40 });
  player1.health->m_screenSpaceTransform.position = player1.offset;
  player1.health->m_screenSpaceTransform.position.x += -212;
  player1.health->SetAlignment(Sigma::UIProgressBar::LEFT);
  player1.border = GET_FACTORY->CreateObject<Sigma::UIImage>("Healthbar Border", "HealthbarRim");
  player1.border->m_screenSpaceTransform.position = player1.offset;
  player1.border->m_screenSpaceTransform.scale = { 432, 40 };

  player1.frame = GET_FACTORY->CreateObject<Sigma::UIImage>("Frame", "PlaceholderFrame");
  player1.frame->m_screenSpaceTransform.position = player1.offset;
  player1.frame->m_screenSpaceTransform.scale = { 120, 96 };
  player1.frame->m_screenSpaceTransform.position.x += -286.0f;
  player1.frame->m_screenSpaceTransform.position.y += 18.0f;

  player1.currentHealth[0] = GET_FACTORY->CreateObject<Sigma::UINumber>("CurrentHealth Decs");
  player1.currentHealth[0]->m_screenSpaceTransform.position = player1.offset;
  player1.currentHealth[0]->m_screenSpaceTransform.scale = { 36, 42 };
  player1.currentHealth[0]->m_screenSpaceTransform.position.x += -200;
  player1.currentHealth[0]->m_screenSpaceTransform.position.y +=   50;
  player1.currentHealth[1] = GET_FACTORY->CreateObject<Sigma::UINumber>("CurrentHealth Units");
  player1.currentHealth[1]->m_screenSpaceTransform.position = player1.offset;
  player1.currentHealth[1]->m_screenSpaceTransform.scale = { 36, 42 };
  player1.currentHealth[1]->m_screenSpaceTransform.position.x += -160;
  player1.currentHealth[1]->m_screenSpaceTransform.position.y +=   50;

  player1.slash = GET_FACTORY->CreateObject<Sigma::UIText>("Slash");
  player1.slash->m_screenSpaceTransform.position = player1.offset;
  player1.slash->m_screenSpaceTransform.scale = { 1.0f, 1.8f };
  player1.slash->m_screenSpaceTransform.position.x += -136;
  player1.slash->m_screenSpaceTransform.position.y +=   28;
  player1.slash->SetText("/");
  player1.slash->SetTint({1.0f, 1.0f, 1.0f, 1.0f});

  player1.maxHealth[0] = GET_FACTORY->CreateObject<Sigma::UINumber>("MaxHealth Decs");
  player1.maxHealth[0]->m_screenSpaceTransform.position = player1.offset;
  player1.maxHealth[0]->m_screenSpaceTransform.scale = { 24, 28 };
  player1.maxHealth[0]->m_screenSpaceTransform.position.x += -103;
  player1.maxHealth[0]->m_screenSpaceTransform.position.y +=   42;
  player1.maxHealth[1] = GET_FACTORY->CreateObject<Sigma::UINumber>("MaxHealth Units");
  player1.maxHealth[1]->m_screenSpaceTransform.position = player1.offset;
  player1.maxHealth[1]->m_screenSpaceTransform.scale = { 24, 28 };
  player1.maxHealth[1]->m_screenSpaceTransform.position.x += -74;
  player1.maxHealth[1]->m_screenSpaceTransform.position.y +=  42;
#pragma endregion

#pragma region Player2
  player2.offset = {600, 420, 0};

  player2.background = GET_FACTORY->CreateObject<Sigma::UIImage>("Healthbar Background", "HealthbarBackground");
  player2.background->m_screenSpaceTransform.scale = { 424, 40 };
  player2.background->m_screenSpaceTransform.position = player2.offset;
  player2.blue = GET_FACTORY->CreateObject<HealthBar>("Healthbar Blue", "HealthbarBlue");
  player2.blue->SetScale({424, 40 });
  player2.blue->m_screenSpaceTransform.position = player2.offset;
  player2.blue->m_screenSpaceTransform.position.x += 212;
  player2.blue->SetAlignment(Sigma::UIProgressBar::RIGHT);
  player2.health = GET_FACTORY->CreateObject<HealthBar>("Healthbar Red", "HealthbarRed");
  player2.health->SetScale({ 424, 40 });
  player2.health->m_screenSpaceTransform.position = player2.offset;
  player2.health->m_screenSpaceTransform.position.x += 212;
  player2.health->SetAlignment(Sigma::UIProgressBar::RIGHT);
  player2.border = GET_FACTORY->CreateObject<Sigma::UIImage>("Healthbar Border", "HealthbarRim");
  player2.border->m_screenSpaceTransform.position = player2.offset;
  player2.border->m_screenSpaceTransform.scale = { 432, 40 };

  player2.frame = GET_FACTORY->CreateObject<Sigma::UIImage>("Frame", "PlaceholderFrame");
  player2.frame->m_screenSpaceTransform.position = player2.offset;
  player2.frame->m_screenSpaceTransform.scale = { 120, 96 };
  player2.frame->m_screenSpaceTransform.position.x += 286.0f;
  player2.frame->m_screenSpaceTransform.position.y += 18.0f;

  player2.currentHealth[0] = GET_FACTORY->CreateObject<Sigma::UINumber>("CurrentHealth Decs");
  player2.currentHealth[0]->m_screenSpaceTransform.position = player2.offset;
  player2.currentHealth[0]->m_screenSpaceTransform.scale = { 36, 42 };
  player2.currentHealth[0]->m_screenSpaceTransform.position.x += -200 + 274;
  player2.currentHealth[0]->m_screenSpaceTransform.position.y +=   50;
  player2.currentHealth[1] = GET_FACTORY->CreateObject<Sigma::UINumber>("CurrentHealth Units");
  player2.currentHealth[1]->m_screenSpaceTransform.position = player2.offset;
  player2.currentHealth[1]->m_screenSpaceTransform.scale = { 36, 42 };
  player2.currentHealth[1]->m_screenSpaceTransform.position.x += -160 + 274;
  player2.currentHealth[1]->m_screenSpaceTransform.position.y +=   50;

  player2.slash = GET_FACTORY->CreateObject<Sigma::UIText>("Slash");
  player2.slash->m_screenSpaceTransform.position = player2.offset;
  player2.slash->m_screenSpaceTransform.scale = { 1.0f, 1.8f };
  player2.slash->m_screenSpaceTransform.position.x += -136 + 274;
  player2.slash->m_screenSpaceTransform.position.y +=   28;
  player2.slash->SetText("/");
  player2.slash->SetTint({1.0f, 1.0f, 1.0f, 1.0f});

  player2.maxHealth[0] = GET_FACTORY->CreateObject<Sigma::UINumber>("MaxHealth Decs");
  player2.maxHealth[0]->m_screenSpaceTransform.position = player2.offset;
  player2.maxHealth[0]->m_screenSpaceTransform.scale = { 24, 28 };
  player2.maxHealth[0]->m_screenSpaceTransform.position.x += -103 + 274;
  player2.maxHealth[0]->m_screenSpaceTransform.position.y +=   42;
  player2.maxHealth[1] = GET_FACTORY->CreateObject<Sigma::UINumber>("MaxHealth Units");
  player2.maxHealth[1]->m_screenSpaceTransform.position = player2.offset;
  player2.maxHealth[1]->m_screenSpaceTransform.scale = { 24, 28 };
  player2.maxHealth[1]->m_screenSpaceTransform.position.x += -74 + 274;
  player2.maxHealth[1]->m_screenSpaceTransform.position.y +=  42;
#pragma endregion

  EnableUIPlayer1(true);
  EnableUIPlayer2(false);


  // Go Indicator
  m_goIndicator = GET_FACTORY->CreateObject<Sigma::UIImage>("Go Indicator", "GO");
  m_goIndicator->m_screenSpaceTransform.position = {400, 50, 0};
  m_goIndicator->m_screenSpaceTransform.scale = {64, 32};
  m_goIndicator->SetActive(false);
  

}

void HUD::EnableUIPlayer1(bool enable) {
  player1.background->SetActive(enable);
  player1.blue->SetActive(enable);
  player1.health->SetActive(enable);
  player1.border->SetActive(enable);
  player1.frame->SetActive(enable);
  player1.currentHealth[0]->SetActive(enable);
  player1.currentHealth[1]->SetActive(enable);
  player1.slash->SetActive(enable);
  player1.maxHealth[0]->SetActive(enable);
  player1.maxHealth[1]->SetActive(enable);
}

void HUD::EnableUIPlayer2(bool enable) {
  player2.background->SetActive(enable);
  player2.blue->SetActive(enable);
  player2.health->SetActive(enable);
  player2.border->SetActive(enable);
  player2.frame->SetActive(enable);
  player2.currentHealth[0]->SetActive(enable);
  player2.currentHealth[1]->SetActive(enable);
  player2.slash->SetActive(enable);
  player2.maxHealth[0]->SetActive(enable);
  player2.maxHealth[1]->SetActive(enable);
}

void HUD::EnableGOIndicator() {
  m_goActive = true;
  m_goTimer = 0;
  m_goTimerFlash = 0;
}

void HUD::Start() {}

void HUD::UpdatePlayerHUD() {
  EnableUIPlayer1(true);
  m_players = GameplayManager::GetInstance()->GetPlayers();
  SetNumbers(player1.maxHealth, std::floor(m_players->operator[](0).player->GetMaxHealth()));
  SetNumbers(player1.currentHealth, std::floor(m_players->operator[](0).player->GetHealth()));
  player1.health->m_maxHealth = m_players->operator[](0).player->GetMaxHealth();
  player1.health->m_currentHealth = m_players->operator[](0).player->GetHealth();
  player1.blue->m_maxHealth = m_players->operator[](0).player->GetMaxHealth();
  player1.blue->m_currentHealth = m_players->operator[](0).player->GetHealth();

  m_players->operator[](0).player->healthBar = &player1;


  if (m_players->at(1).player != nullptr) {
    EnableUIPlayer2(true);
    SetNumbers(player2.maxHealth, std::floor(m_players->operator[](1).player->GetMaxHealth()));
    SetNumbers(player2.currentHealth, std::floor(m_players->operator[](1).player->GetHealth()));
    player2.health->m_maxHealth = m_players->operator[](1).player->GetMaxHealth();
    player2.health->m_currentHealth = m_players->operator[](1).player->GetHealth();
    player2.blue->m_maxHealth = m_players->operator[](1).player->GetMaxHealth();
    player2.blue->m_currentHealth = m_players->operator[](1).player->GetHealth();

    m_players->operator[](1).player->healthBar = &player2;
  }
}

void HUD::Update(double delta) {
  if(m_goActive){
    m_goTimer += delta;
    m_goTimerFlash += delta;

    if(m_goTimerFlash >= m_goTimeFlash){
      m_goIndicator->SetActive(!m_goIndicator->IsActive());
      m_goTimerFlash = 0;
    }
    if(m_goTimer >= m_goMaxTimer){
      m_goActive = false;
      m_goIndicator->SetActive(false);
    }
  }
}


void HUD::SetNumbers(std::array<Sigma::UINumber *, 2> numbers, int value) {
  value = glm::clamp(value, 0, 99);
  numbers[0]->Change(value / 10);
  numbers[1]->Change(value % 10);
}

void HUD::SetPlayer1Health(int health) {}

} // namespace game
