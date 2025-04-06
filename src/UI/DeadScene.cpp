#include "DeadScene.hpp"
#include "MainMenu.hpp"
#include "Controller/CameraController.hpp"
#include "Level1/Scene1.hpp"
#include "Objects/Camera.hpp"
#include "UI/SceneButton.hpp"

void game::DeadScene::Load() {

  std::string m_jsonPath = "assets/UI/Score.Json";

  if (m_jsonPath.empty())
    return;

  std::fstream file(m_jsonPath);

  if (!file.is_open()) {
    std::cout << "[GameScene] " << GetName() << " failed to open JSON file " << m_jsonPath << '\n';
    return;
  }

  std::cout << "[GameScene] " << GetName() << " Loading JSON file: " << m_jsonPath << '\n';

  Sigma::json_t J = Sigma::json_t::parse(file);

  file.close();

  m_topScore = J["topScore"];
  m_playerScore = J["playerScore"];

  std::cout << "[GameScene] " << GetName() << " JSON file loaded\n";

  J.clear();

  Scene::Load();

  GET_CAMERA->SetCurrentCamera(GET_FACTORY->CreateObject<Sigma::Camera>("Main Camera"));

  m_background = GET_FACTORY->CreateObject<Sigma::Actor>();
  m_background->SetTexture("assets/UI/Sprites/Menu_Background.png");
  m_background->transform.scale = {960.0f, 500.0f};
  m_background->transform.position.z = -5000;

  AddChild(m_background);

  m_death = GET_FACTORY->CreateObject<Sigma::Actor>();
  m_death->SetTexture("assets/UI/Sprites/Death.png");
  m_death->transform.scale = {400.0f, 100.0f};

  AddChild(m_death);

  auto m = new game::MainMenu("Game Scene1", 0);
  m_quitButton = GET_FACTORY->CreateObject<Sigma::SceneButton>("Quit Button", m ,GetID());
  m_quitButton->m_screenSpaceTransform.scale = {200, 100};
  m_quitButton->m_screenSpaceTransform.position.y -= 340;
  m_quitButton->SetTexture("assets/UI/Sprites/Exit_Sign.png");

  AddChild(m_quitButton);

  AddChild(GET_CAMERA->GetCurrentCamera());

  m_top.numbers.resize(game::UIMoneyBar::maxDigits);
  for (short i = 0; i < game::UIMoneyBar::maxDigits; i++) {
    m_top.numbers[i] = GET_FACTORY->CreateObject<Sigma::UINumber>("Money Digit " + std::to_string(i));
    m_top.numbers[i]->m_screenSpaceTransform.position = m_top.offset;
    m_top.numbers[i]->m_screenSpaceTransform.scale = m_top.numScale;
    m_top.numbers[i]->m_screenSpaceTransform.position.x += game::UIMoneyBar::leftX + i * 60.0f;
    AddChild(m_top.numbers[i]);
  }
  m_top.cashIcon = GET_FACTORY->CreateObject<Sigma::UIImage>("Cash Icon", "Dollar");
  m_top.cashIcon->m_screenSpaceTransform.position = m_top.offset;
  m_top.cashIcon->m_screenSpaceTransform.scale = m_top.numScale;
  m_top.cashIcon->m_screenSpaceTransform.position.x -= game::UIMoneyBar::leftX;
  AddChild(m_top.cashIcon);
  m_top.active = true;

  m_top.startCash = m_top.displayedCash;
  m_top.endCash = glm::clamp(m_topScore, 0, m_top.maxCash);
  m_top.timer = 0.0f;

}

void game::DeadScene::Update(double delta) {
  Scene::Update(delta);
  // Money
  if (m_top.active && (m_top.displayedCash != m_top.endCash)) {
    m_top.DisplayMoney(m_top.LerpMoney(delta));
  }
}

void game::DeadScene::Unload() {
  Scene::Unload();
}