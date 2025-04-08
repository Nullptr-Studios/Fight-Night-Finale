#include "WinScene.hpp"
#include "MainMenu.hpp"
#include "Controller/CameraController.hpp"
#include "Level1/Scene1.hpp"
#include "Objects/Camera.hpp"
#include "UI/SceneButton.hpp"

void game::WinScene::Load() {

  GameplayManager::GetInstance()->enableComboScore(false);

  //Sanity
  if (m_scoreJson.empty())
    return;

  //Read
  std::fstream file(m_scoreJson);
  if (!file.is_open()) {
    std::cout << "[GameScene] " << GetName() << " failed to open JSON file " << m_scoreJson << '\n';
    return;
  }

  std::cout << "[GameScene] " << GetName() << " Loading JSON file: " << m_scoreJson << '\n';
  Sigma::json_t J = Sigma::json_t::parse(file);

  m_topScore = J["topScore"];
  m_currentScore = J["playerScore"];

  file.close();
  J.clear();

  std::cout << "[GameScene] " << GetName() << " JSON file loaded\n";

  //Scene Stuff
  Scene::Load();

  GET_CAMERA->SetCurrentCamera(GET_FACTORY->CreateObject<Sigma::Camera>("Main Camera"));

  m_background = GET_FACTORY->CreateObject<Sigma::Actor>();
  m_background->SetTexture("assets/UI/Sprites/Menu_Background.png");
  m_background->transform.scale = {960.0f, 500.0f};
  m_background->transform.position.z = -5000;

  AddChild(m_background);

  m_death = GET_FACTORY->CreateObject<Sigma::Actor>();
  m_death->SetTexture("assets/UI/Sprites/Win.png");
  m_death->transform.scale = {400.0f, 100.0f};
  m_death->transform.position.y = 116;

  AddChild(m_death);

  auto m = new game::MainMenu("Game Scene1", 0);
  m_quitButton = GET_FACTORY->CreateObject<Sigma::SceneButton>("Quit Button", m ,GetID());
  m_quitButton->m_screenSpaceTransform.scale = {200, 100};
  m_quitButton->m_screenSpaceTransform.position.y -= 340;
  m_quitButton->SetTexture("assets/UI/Sprites/Exit_Sign.png");

  AddChild(m_quitButton);

  AddChild(GET_CAMERA->GetCurrentCamera());

#pragma region topScore
  //TOP SCORE
  m_topText = GET_FACTORY->CreateObject<Sigma::Actor>();
  m_topText->SetTexture("assets/UI/Sprites/topScore.png");
  m_topText->transform.scale = {90.0f, 26.0f};
  m_topText->transform.position.y = 40;

  AddChild(m_topText);

  m_top.offset.y = 58;
  m_top.offsetMultiplier = 45;
  m_top.numScale = {40.5f,47.25f};
  m_top.numbers.resize(game::UIMoneyBar::maxDigits);
  m_top.leftX = -m_top.offsetMultiplier * game::UIMoneyBar::maxDigits / 2.0f;
  for (short i = 0; i < game::UIMoneyBar::maxDigits; i++) {
    m_top.numbers[i] = GET_FACTORY->CreateObject<Sigma::UINumber>("Money Digit " + std::to_string(i));
    m_top.numbers[i]->m_screenSpaceTransform.position = m_top.offset;
    m_top.numbers[i]->m_screenSpaceTransform.scale = m_top.numScale;
    m_top.numbers[i]->m_screenSpaceTransform.position.x += m_top.leftX + i * m_top.offsetMultiplier;
    AddChild(m_top.numbers[i]);
  }
  m_top.cashIcon = GET_FACTORY->CreateObject<Sigma::UIImage>("Cash Icon", "Dollar");
  m_top.cashIcon->m_screenSpaceTransform.position = m_top.offset;
  m_top.cashIcon->m_screenSpaceTransform.scale = m_top.numScale;
  m_top.cashIcon->m_screenSpaceTransform.position.x -= m_top.leftX;
  AddChild(m_top.cashIcon);
  m_top.active = true;

  m_top.startCash = m_top.displayedCash;
  m_top.endCash = glm::clamp(m_topScore, 0, m_top.maxCash);
  m_top.timer = 0.0f;

#pragma endregion topScore

#pragma region currentScore
  //CURRENT SCORE
  m_currentText = GET_FACTORY->CreateObject<Sigma::Actor>();
  m_currentText->SetTexture("assets/UI/Sprites/currentScore.png");
  m_currentText->transform.scale = {168.0f, 32.0f};
  m_currentText->transform.position.y = -24;

  AddChild(m_currentText);

  m_current.offset.y = -137;
  m_current.numbers.resize(game::UIMoneyBar::maxDigits);
  m_current.leftX = -m_current.offsetMultiplier * game::UIMoneyBar::maxDigits / 2.0f;
  for (short i = 0; i < game::UIMoneyBar::maxDigits; i++) {
    m_current.numbers[i] = GET_FACTORY->CreateObject<Sigma::UINumber>("Money Digit " + std::to_string(i));
    m_current.numbers[i]->m_screenSpaceTransform.position = m_current.offset;
    m_current.numbers[i]->m_screenSpaceTransform.scale = m_current.numScale;
    m_current.numbers[i]->m_screenSpaceTransform.position.x += m_current.leftX + i * 60.0f;
    AddChild(m_current.numbers[i]);
  }
  m_current.cashIcon = GET_FACTORY->CreateObject<Sigma::UIImage>("Cash Icon", "Dollar");
  m_current.cashIcon->m_screenSpaceTransform.position = m_current.offset;
  m_current.cashIcon->m_screenSpaceTransform.scale = m_current.numScale;
  m_current.cashIcon->m_screenSpaceTransform.position.x -= m_current.leftX;
  AddChild(m_current.cashIcon);
  m_current.active = true;

  m_current.startCash = m_current.displayedCash;
  m_current.endCash = glm::clamp(m_currentScore, 0, m_current.maxCash);
  m_current.timer = 0.0f;

#pragma endregion currentScore


  AddChild(GET_CAMERA->GetCurrentCamera());
  GameplayManager::GetInstance()->UninitializeGame();

}

void game::WinScene::Update(double delta) {
  Scene::Update(delta);
  // Top
  if (m_top.active && (m_top.displayedCash != m_top.endCash)) {
    m_top.DisplayMoney(m_top.LerpMoney(delta));
  }
  // Current
  if (m_current.active && (m_current.displayedCash != m_current.endCash)) {
    m_current.DisplayMoney(m_current.LerpMoney(delta));
  }
}

void game::WinScene::Unload() {
  Scene::Unload();
}