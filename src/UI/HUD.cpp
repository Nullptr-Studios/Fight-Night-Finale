#include "HUD.hpp"
#include "Core.hpp"
#include "Factory.hpp"
#include "GameManager.hpp"
#include "MainMenu.hpp"
#include "Objects/Manager/GameplayManager.hpp"
#include "Player/Player.hpp"
#include "UI/HealthBar.hpp"
#include "UI/UIFade.hpp"
#include "UI/UIImage.hpp"
#include "UI/UINumber.hpp"
#include "UI/UIText.hpp"


namespace game {

HUD::~HUD() {
  delete player1.comboShake;
  delete player2.comboShake;
}

void HUD::Init() {
#pragma region Player1
  player1.offset = {-600, 450, 0};

  player1.background = GET_FACTORY->CreateObject<Sigma::UIImage>("Healthbar Background P1", "HealthbarBackground");
  player1.background->m_screenSpaceTransform.scale = {424, 34};
  player1.background->m_screenSpaceTransform.position = player1.offset;
  player1.blue = GET_FACTORY->CreateObject<HealthBar>("Healthbar Blue P1", "HealthbarBlue");
  player1.blue->SetScale({424, 34});
  player1.blue->m_screenSpaceTransform.position = player1.offset;
  player1.blue->m_screenSpaceTransform.position.x += -212;
  player1.blue->SetAlignment(Sigma::UIProgressBar::LEFT);
  player1.health = GET_FACTORY->CreateObject<HealthBar>("Healthbar Red P1", "HealthbarRed");
  player1.health->SetScale({424, 34});
  player1.health->m_screenSpaceTransform.position = player1.offset;
  player1.health->m_screenSpaceTransform.position.x += -212;
  player1.health->SetAlignment(Sigma::UIProgressBar::LEFT);
  player1.border = GET_FACTORY->CreateObject<Sigma::UIImage>("Healthbar Border P1", "HealthbarRim");
  player1.border->m_screenSpaceTransform.position = player1.offset;
  player1.border->m_screenSpaceTransform.scale = {432, 40};

  player1.frame = GET_FACTORY->CreateObject<Sigma::UIImage>("Frame P1", "CharacterFrame");
  player1.frame->m_screenSpaceTransform.position = player1.offset;
  player1.frame->m_screenSpaceTransform.scale = {120, 96};
  player1.frame->m_screenSpaceTransform.position.x += -286.0f;
  player1.frame->m_screenSpaceTransform.position.y += 18.0f;
  player1.frameImage = GET_FACTORY->CreateObject<Sigma::UIImage>("Frame P1 Iamge", "PlayerUI");
  player1.frameImage->m_animComp->GotoFrame(0);
  player1.frameImage->m_screenSpaceTransform.position = player1.offset;
  player1.frameImage->m_screenSpaceTransform.scale = {86, 88};
  player1.frameImage->m_screenSpaceTransform.position.x += -286.0f;
  player1.frameImage->m_screenSpaceTransform.position.y += 18.0f;


  player1.currentHealth[0] = GET_FACTORY->CreateObject<Sigma::UINumber>("CurrentHealth Decs P1");
  player1.currentHealth[0]->m_screenSpaceTransform.position = player1.offset;
  player1.currentHealth[0]->m_screenSpaceTransform.scale = {36, 42};
  player1.currentHealth[0]->m_screenSpaceTransform.position.x += -200;
  player1.currentHealth[0]->m_screenSpaceTransform.position.y += 50;
  player1.currentHealth[1] = GET_FACTORY->CreateObject<Sigma::UINumber>("CurrentHealth Units P1");
  player1.currentHealth[1]->m_screenSpaceTransform.position = player1.offset;
  player1.currentHealth[1]->m_screenSpaceTransform.scale = {36, 42};
  player1.currentHealth[1]->m_screenSpaceTransform.position.x += -160;
  player1.currentHealth[1]->m_screenSpaceTransform.position.y += 50;

  player1.slash = GET_FACTORY->CreateObject<Sigma::UIText>("Slash P1");
  player1.slash->m_screenSpaceTransform.position = player1.offset;
  player1.slash->m_screenSpaceTransform.scale = {1.0f, 1.8f};
  player1.slash->m_screenSpaceTransform.position.x += -136;
  player1.slash->m_screenSpaceTransform.position.y += 28;
  player1.slash->m_screenSpaceTransform.scale = {.75f, .75f};
  player1.slash->SetText("/");
  player1.slash->SetTint({1.0f, 1.0f, 1.0f, 1.0f});

  player1.maxHealth[0] = GET_FACTORY->CreateObject<Sigma::UINumber>("MaxHealth Decs P1");
  player1.maxHealth[0]->m_screenSpaceTransform.position = player1.offset;
  player1.maxHealth[0]->m_screenSpaceTransform.scale = {24, 28};
  player1.maxHealth[0]->m_screenSpaceTransform.position.x += -103;
  player1.maxHealth[0]->m_screenSpaceTransform.position.y += 42;
  player1.maxHealth[1] = GET_FACTORY->CreateObject<Sigma::UINumber>("MaxHealth Units P1");
  player1.maxHealth[1]->m_screenSpaceTransform.position = player1.offset;
  player1.maxHealth[1]->m_screenSpaceTransform.scale = {24, 28};
  player1.maxHealth[1]->m_screenSpaceTransform.position.x += -74;
  player1.maxHealth[1]->m_screenSpaceTransform.position.y += 42;

  // Combo UI
  player1.comboText = GET_FACTORY->CreateObject<Sigma::UIText>("Combo Text P1");
  player1.comboText->m_screenSpaceTransform.position = player1.offset + glm::vec3(-286, -128, 0);
  player1.comboText->SetTint({1.0f, 1.0f, 1.0f, 1.0f});
  player1.comboText->SetText(" ");

  // shake combo
  player1.comboShake = new Sigma::ShakeObject();

#pragma endregion

#pragma region Player2
  player2.offset = {600, 450, 0};

  player2.background = GET_FACTORY->CreateObject<Sigma::UIImage>("Healthbar Background P1", "HealthbarBackground");
  player2.background->m_screenSpaceTransform.scale = {424, 34};
  player2.background->m_screenSpaceTransform.position = player2.offset;
  player2.blue = GET_FACTORY->CreateObject<HealthBar>("Healthbar Blue P2", "HealthbarBlue");
  player2.blue->SetScale({424, 34});
  player2.blue->m_screenSpaceTransform.position = player2.offset;
  player2.blue->m_screenSpaceTransform.position.x += 212;
  player2.blue->SetAlignment(Sigma::UIProgressBar::RIGHT);
  player2.health = GET_FACTORY->CreateObject<HealthBar>("Healthbar Red P2", "HealthbarRed");
  player2.health->SetScale({424, 34});
  player2.health->m_screenSpaceTransform.position = player2.offset;
  player2.health->m_screenSpaceTransform.position.x += 212;
  player2.health->SetAlignment(Sigma::UIProgressBar::RIGHT);
  player2.border = GET_FACTORY->CreateObject<Sigma::UIImage>("Healthbar Border P2", "HealthbarRim");
  player2.border->m_screenSpaceTransform.position = player2.offset;
  player2.border->m_screenSpaceTransform.scale = {432, 40};

  player2.frame = GET_FACTORY->CreateObject<Sigma::UIImage>("Frame P2", "CharacterFrame");
  player2.frame->m_screenSpaceTransform.position = player2.offset;
  player2.frame->m_screenSpaceTransform.scale = {120, 96};
  player2.frame->m_screenSpaceTransform.position.x += 286.0f;
  player2.frame->m_screenSpaceTransform.position.y += 18.0f;
  player2.frameImage = GET_FACTORY->CreateObject<Sigma::UIImage>("Frame P2 Iamge", "PlayerUI");
  player2.frameImage->m_animComp->GotoFrame(1);
  player2.frameImage->m_screenSpaceTransform.position = player2.offset;
  player2.frameImage->m_screenSpaceTransform.scale = {-86, 88};
  player2.frameImage->m_screenSpaceTransform.position.x += 286.0f;
  player2.frameImage->m_screenSpaceTransform.position.y += 18.0f;

  player2.currentHealth[0] = GET_FACTORY->CreateObject<Sigma::UINumber>("CurrentHealth Decs P2");
  player2.currentHealth[0]->m_screenSpaceTransform.position = player2.offset;
  player2.currentHealth[0]->m_screenSpaceTransform.scale = {36, 42};
  player2.currentHealth[0]->m_screenSpaceTransform.position.x += -200 + 274;
  player2.currentHealth[0]->m_screenSpaceTransform.position.y += 50;
  player2.currentHealth[1] = GET_FACTORY->CreateObject<Sigma::UINumber>("CurrentHealth Units P2");
  player2.currentHealth[1]->m_screenSpaceTransform.position = player2.offset;
  player2.currentHealth[1]->m_screenSpaceTransform.scale = {36, 42};
  player2.currentHealth[1]->m_screenSpaceTransform.position.x += -160 + 274;
  player2.currentHealth[1]->m_screenSpaceTransform.position.y += 50;

  player2.slash = GET_FACTORY->CreateObject<Sigma::UIText>("Slash P2");
  player2.slash->m_screenSpaceTransform.position = player2.offset;
  player2.slash->m_screenSpaceTransform.scale = {1.0f, 1.8f};
  player2.slash->m_screenSpaceTransform.position.x += -136 + 274;
  player2.slash->m_screenSpaceTransform.position.y += 28;
  player2.slash->SetText("/");
  player2.slash->SetTint({1.0f, 1.0f, 1.0f, 1.0f});

  player2.maxHealth[0] = GET_FACTORY->CreateObject<Sigma::UINumber>("MaxHealth Decs P2");
  player2.maxHealth[0]->m_screenSpaceTransform.position = player2.offset;
  player2.maxHealth[0]->m_screenSpaceTransform.scale = {24, 28};
  player2.maxHealth[0]->m_screenSpaceTransform.position.x += -103 + 274;
  player2.maxHealth[0]->m_screenSpaceTransform.position.y += 42;
  player2.maxHealth[1] = GET_FACTORY->CreateObject<Sigma::UINumber>("MaxHealth Units P2");
  player2.maxHealth[1]->m_screenSpaceTransform.position = player2.offset;
  player2.maxHealth[1]->m_screenSpaceTransform.scale = {24, 28};
  player2.maxHealth[1]->m_screenSpaceTransform.position.x += -74 + 274;
  player2.maxHealth[1]->m_screenSpaceTransform.position.y += 42;

  player2.comboText = GET_FACTORY->CreateObject<Sigma::UIText>("Combo Text P1");
  player2.comboText->m_screenSpaceTransform.position = player2.offset + glm::vec3(-286, -128, 0);
  player2.comboText->SetTint({1.0f, 1.0f, 1.0f, 1.0f});
  player2.comboText->SetText(" ");

  player2.comboShake = new Sigma::ShakeObject();
#pragma endregion

  EnableUIPlayer1(false);
  EnableUIPlayer2(false);

  // Go Indicator
  m_goIndicator = GET_FACTORY->CreateObject<Sigma::UIImage>("Go Indicator", "GO");
  m_goIndicator->m_screenSpaceTransform.position = {800, 140, 0};
  m_goIndicator->m_screenSpaceTransform.scale = {256, 128};
  m_goIndicator->SetActive(false);

#pragma region XPBar
  money.numbers.resize(game::UIMoneyBar::maxDigits);
  money.leftX = -money.offsetMultiplier * game::UIMoneyBar::maxDigits / 2.0f;
  for (short i = 0; i < game::UIMoneyBar::maxDigits; i++) {
    money.numbers[i] = GET_FACTORY->CreateObject<Sigma::UINumber>("Money Digit " + std::to_string(i));
    money.numbers[i]->m_screenSpaceTransform.position = money.offset;
    money.numbers[i]->m_screenSpaceTransform.scale = money.numScale;
    money.numbers[i]->m_screenSpaceTransform.position.x += money.leftX + i * money.offsetMultiplier;
  }

  // money.cashIcon = GET_FACTORY->CreateObject<Sigma::UIElement>("Cash Icon");
  // money.cashIcon->SetTexture("assets/UI/Sprites/Dollar.png");
  money.cashIcon = GET_FACTORY->CreateObject<Sigma::UIImage>("Cash Icon", "Dollar");
  money.cashIcon->m_screenSpaceTransform.position = money.offset;
  money.cashIcon->m_screenSpaceTransform.scale = money.numScale;
  money.cashIcon->m_screenSpaceTransform.position.x -= money.leftX;

#pragma endregion

#pragma region PauseMenu

  pauseMenu.m_background = GET_FACTORY->CreateObject<Sigma::UIElement>("Pause Background");
  pauseMenu.m_background->SetTexture("assets/UI/Paused.png");
  pauseMenu.m_background->m_screenSpaceTransform.scale = {1920,1080};

#pragma endregion


  m_fadeScreen = GET_FACTORY->CreateObject<Sigma::UIFade>("Fade Screen", "White");

  m_fadeScreen->m_screenSpaceTransform.scale = {1920, 1080};

  EnableUIMoney(false);
  EnableUIPauseMenu(false);
}

void HUD::EnableUIMoney(bool enable) {
  money.DisplayMoney(0);
  for (short i = 0; i < game::UIMoneyBar::maxDigits; i++) {
    money.numbers[i]->SetActive(enable);
  }
  money.cashIcon->SetActive(enable);
  money.active = enable;
  money.startCash = 0;
  money.endCash = 0;
  money.timer = 0.0f;
}

void HUD::EnableUIPauseMenu(bool enable) {
  pauseMenu.m_background->SetActive(enable);
  pauseMenu.active = enable;
}

void HUD::EnableUIPlayer1(bool enable) {
  player1.background->SetActive(enable);
  player1.blue->SetActive(enable);
  player1.health->SetActive(enable);
  player1.border->SetActive(enable);
  player1.frame->SetActive(enable);
  player1.frameImage->SetActive(enable);
  player1.currentHealth[0]->SetActive(enable);
  player1.currentHealth[1]->SetActive(enable);
  player1.slash->SetActive(enable);
  player1.maxHealth[0]->SetActive(enable);
  player1.maxHealth[1]->SetActive(enable);

  player1.comboText->SetActive(enable);
  player1.comboText->SetTint({1,1,1,0});
  player1.combo = 0;
}

void HUD::EnableUIPlayer2(bool enable) {
  player2.background->SetActive(enable);
  player2.blue->SetActive(enable);
  player2.health->SetActive(enable);
  player2.border->SetActive(enable);
  player2.frame->SetActive(enable);
  player2.frameImage->SetActive(enable);
  player2.currentHealth[0]->SetActive(enable);
  player2.currentHealth[1]->SetActive(enable);
  player2.slash->SetActive(enable);
  player2.maxHealth[0]->SetActive(enable);
  player2.maxHealth[1]->SetActive(enable);
  
  player2.comboText->SetActive(enable);
  player2.comboText->SetTint({1,1,1,0});
  player2.combo = 0;
}

void HUD::EnableGOIndicator() {
  m_goActive = true;
  m_goTimer = 0;
  m_goTimerFlash = 0;
}

void HUD::Start() {}

void HUD::UpdatePlayerHUD() {
  EnableUIMoney(true);

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
  if (m_goActive) {
    m_goTimer += delta;
    m_goTimerFlash += delta;

    if (m_goTimerFlash >= m_goTimeFlash) {
      m_goIndicator->SetActive(!m_goIndicator->IsActive());
      m_goTimerFlash = 0;
    }
    if (m_goTimer >= m_goMaxTimer) {
      m_goActive = false;
      m_goIndicator->SetActive(false);
    }
  }

  if (player1.combo > 0) {
    player1.m_comboDisapear -= delta;
    if (player1.m_comboDisapear <= 0) {
      player1.m_comboDisapear = 5.0f;
      player1.ComboSuccesfull();
      player1.combo = 0;
    }
  }

  if (player2.combo > 0) {
    player2.m_comboDisapear -= delta;
    if (player2.m_comboDisapear <= 0) {
      player2.m_comboDisapear = 5.0f;
      player2.ComboSuccesfull();
      player2.combo = 0;
    }
  }

  player1.comboShake->ShakeUpdate(delta);
  player1.comboText->m_screenSpaceTransform.position = player1.offset + glm::vec3(-286, -128, 0)
          + glm::vec3(player1.comboShake->GetShakeOffset().x, player1.comboShake->GetShakeOffset().y, 0);

  player2.comboShake->ShakeUpdate(delta);
  player2.comboText->m_screenSpaceTransform.position = player2.offset + glm::vec3(-286, -128, 0) 
          + glm::vec3(player2.comboShake->GetShakeOffset().x, player2.comboShake->GetShakeOffset().y, 0);

  // Money
  if (money.active && (money.displayedCash != money.endCash)) {
    money.DisplayMoney(money.LerpMoney(delta));
  }
}


void HUD::SetNumbers(std::array<std::shared_ptr<Sigma::UINumber>, 2> numbers, int value) {
  value = glm::clamp(value, 0, 99);
  numbers[0]->Change(value / 10);
  numbers[1]->Change(value % 10);
}


void HUD::Enable() {
  EnableUIMoney(false);
  EnableUIPlayer1(false);
  EnableUIPlayer2(false);
  EnableUIPauseMenu(false);
  m_fadeScreen->ToggleDisable(true);
}
void HUD::Disable() {
  EnableUIPlayer1(false);
  EnableUIPlayer2(false);
  EnableUIMoney(false);
  EnableUIPauseMenu(false);
  m_fadeScreen->ToggleDisable(false);
}

void HUD::DoInitialSceneText(std::string text) {
  
}

void HUD::UpdateXP(int currentXP) {
  money.startCash = money.displayedCash;
  money.endCash = glm::clamp(currentXP, 0, money.maxCash);
  money.timer = 0.0f;
}

void HUD::EnableGiveComboScore(bool enable) {
  player1.giveScore = enable;
  player2.giveScore = enable;
  player1.combo = 0;
  player2.combo = 0;
  player1.ComboBreak();
  player2.ComboBreak();
}

} // namespace game