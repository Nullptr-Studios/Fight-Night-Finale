//
// Created by Dario on 03/03/2025.
//

#include "GameplayManager.hpp"

#include "Audio/AudioEngine.hpp"
#include "Controller/CameraController.hpp"
#include "Core.hpp"
#include "Factory.hpp"
#include "GameManager.hpp"

#include "Objects/CameraFollow.hpp"

#include "Player/Player.hpp"
#include "UI/DeadScene.hpp"
#include "UI/MainMenu.hpp"


game::GameplayManager* game::GameplayManager::m_instance = nullptr;

void game::GameplayManager::Init() {
  Object::Init();

#ifdef DEBUG_CAMERA
  GET_CAMERA->SetCurrentCamera(GET_FACTORY->CreateObject<Sigma::Camera>("Debug Camera"));
  GET_CAMERA->GetCurrentCamera()->size = 1;
#else
  m_cameraFollow = GET_FACTORY->CreateObject<Sigma::CameraFollow>("Main Camera Follow");
  m_cameraFollow->size = 3.5;
  GET_CAMERA->SetCurrentCamera(m_cameraFollow);
#endif


  m_gameHud = GET_FACTORY->CreateObject<game::HUD>("Game HUD");

  GET_AUDIO->LoadBank("assets/Sound/Desktop/Master.bank");
  GET_AUDIO->LoadBank("assets/Sound/Desktop/Master.strings.bank");
  GET_AUDIO->LoadBank("assets/Sound/Desktop/Music.bank");
  GET_AUDIO->LoadBank("assets/Sound/Desktop/SFX.bank");
  GET_AUDIO->LoadEvent("event:/Music/MainMusic");

}
void game::GameplayManager::Start() {
  Object::Start();
  //StartGame();
  
}
void game::GameplayManager::FirstUpdate(double deltaTime) {
  Object::FirstUpdate(deltaTime);
  // Update the current game scene, and for now teleport players
  if (m_gameSceneIsDirty) {
    GotoNextSceneAfter();
  }
}

void game::GameplayManager::Update(double deltaTime) {
  Object::Update(deltaTime);

  if (!m_playerCount && AEInputGamepadButtonPressed(0, AE_GAMEPAD_START)) {
    InitPlayer(0);
  } else if (!m_playerCount && AEInputKeyPressed(' ')) {
    InitPlayer(-1);
  }
  CheckForCoop();

  int dedPlayers = 0;
  for (const auto& element: m_players) {
    if (element.player == nullptr)
      continue;

    if (!element.player->IsActive()) {
      dedPlayers++;
    }
  }

  if (dedPlayers >= m_playerCount && m_playerCount != 0) {
    storeScore();
    GET_MANAGER->LoadScene(new DeadScene("Dead Scene", 0));
    GET_MANAGER->UnloadScene(m_currentGameScene->GetID());
    UninitializeGame();
  }

  //Pause and Exit
  if (AEInputKeyTriggered(27)
    or AEInputGamepadButtonTriggered(0, AE_GAMEPAD_START)
    or AEInputGamepadButtonTriggered(1, AE_GAMEPAD_START)) {

    //Return to Main Menu
    if (m_paused == true && (AEInputKeyTriggered(27)
    or AEInputGamepadButtonTriggered(0, AE_GAMEPAD_START)
    or AEInputGamepadButtonTriggered(1, AE_GAMEPAD_START))) {
      m_paused = false;
      m_gameHud->EnableUIPauseMenu(m_paused);
      GET_MANAGER->UnloadScene(GameplayManager::GetInstance()->GetCurrentGameScene()->GetID());
      GameplayManager::GetInstance()->UninitializeGame();
      GET_MANAGER->LoadScene(new MainMenu("Main Menu", 0));
    }

    //Pause
    else {
      m_paused = true;
      m_gameHud->EnableUIPauseMenu(m_paused);
    }
  }

  //Unpause
  if (m_paused == true && (AEInputKeyTriggered(' ')
    or AEInputGamepadButtonTriggered(0, AE_GAMEPAD_A)
    or AEInputGamepadButtonTriggered(1, AE_GAMEPAD_A))) {
      m_paused = false;
      m_gameHud->EnableUIPauseMenu(m_paused);
  }

  // Debug pass level
  if (AEInputKeyTriggered('P')) {
    GotoNextScene();
  }
  
}

void game::GameplayManager::RespawnPlayer(game::Player *player) {
  if (m_currentGameScene)
    player->transform.position = {m_currentGameScene->GetPlayerStartPos().x, m_currentGameScene->GetPlayerStartPos().y,
                                  -m_currentGameScene->GetPlayerStartPos().y};
  // player->SetTint(glm::vec4(1));
  // player->SetAlive(true);
  // player->ResetHealth();
  // player->SetActive(true);
  // player->m_animComp->SetCurrentAnim("Idle");
  // player->m_animComp->PlayAnim();
  player->Respawn();
}
void game::GameplayManager::SetPlayerAsDead(Object* player) {
  m_cameraFollow->targets.erase(std::remove(m_cameraFollow->targets.begin(), m_cameraFollow->targets.end(), player), m_cameraFollow->targets.end());
  player->SetActive(false);
}

void game::GameplayManager::TeleportPlayersToNextScene() {
  for (const auto& ps: m_players) {
    if (ps.player) {
      ps.player->transform.position = {m_currentGameScene->GetPlayerStartPos().x, m_currentGameScene->GetPlayerStartPos().y,
                                  -m_currentGameScene->GetPlayerStartPos().y};
      // ps.player->Respawn();
      ps.player->SetSceneBoundsPoly(m_currentGameScene->GetSceneBoundsPoly());
    }
  }
}

void game::GameplayManager::InitPlayer(unsigned controllerID)
{
  PlayerStruct p {};
  p.player = GET_FACTORY->CreateObject<game::Player>("Player", controllerID, "assets/characters/player/behaviour.json", m_playerCount > 0);

  // Add player to the array
  m_players[m_playerCount] = p;

  m_gameHud->UpdatePlayerHUD();

  // Setup Camera
  /*if (m_playerCount == 0) 
    m_cameraFollow->m_targetP1 = p.player.get();
  else
    m_cameraFollow->m_targetP2 = p.player.get();*/

  m_cameraFollow->targets.push_back(p.player.get());

  RespawnPlayer(p.player.get());
  
  p.player->SetSceneBoundsPoly(m_currentGameScene->GetSceneBoundsPoly());
  
  
  m_playerCount++;
}

void game::GameplayManager::CheckForCoop() {
  // If pressed key 2 create 2nd player
  if (m_playerCount == 2 || m_playerCount == 0)
      return;
  if (m_players[0].player->GetControllerID() <= -1 && AEInputGamepadButtonTriggered(0, AE_GAMEPAD_START)) {
    InitPlayer(0);
    RespawnPlayer(m_players[1].player.get());
  } else if (AEInputGamepadButtonTriggered(1, AE_GAMEPAD_START)) {
    InitPlayer(1);
    RespawnPlayer(m_players[1].player.get());
    }
}

  void game::GameplayManager::UpdateCurrentGameScene() {
  m_currentGameScene = dynamic_cast<game::GameScene *>(*GET_SCENES->begin());
  m_gameSceneIsDirty = false;
}

void game::GameplayManager::GotoNextScene() {

  // Do the scene transition
  m_gameHud->m_fadeScreen->FadeIn(.5f, [this]() {
    GET_MANAGER->LoadScene(m_currentGameScene->GetNextScene());
    GET_MANAGER->UnloadScene(m_currentGameScene->GetID());
    //Because the scene is being unloaded at late update wee need to wait till next frame to update the current scene
    m_gameSceneIsDirty = true;
    m_gameHud->m_fadeScreen->FadeOut(.5f);
  });

  //TODO: Add notification thing
  
}

void game::GameplayManager::GotoNextSceneAfter() {
  if (m_uninitializeGame)
    return;
  UpdateCurrentGameScene();
  TeleportPlayersToNextScene();
  
  AEDbgAssertFunction(m_players[0].player != nullptr, __FILE__, __LINE__, "m_player[0] is nullptr");
  m_cameraFollow->transform.position.x = m_players[0].player->transform.position.x;
  m_cameraFollow->transform.position.y = m_players[0].player->transform.position.y + m_cameraFollow->offset;
}

void game::GameplayManager::FinishedAnSpawner() { /*m_gameHud->EnableGOIndicator();*/ }

void game::GameplayManager::EnableHUD() { m_gameHud->Enable(); }
void game::GameplayManager::DisableHUD() { m_gameHud->Disable(); }

void game::GameplayManager::OnScenePass() {
  m_gameHud->EnableGOIndicator();
}

void game::GameplayManager::UninitializeGame() {
  DisableHUD();
  SetActive(false);
  m_uninitializeGame = true;

  for (const auto& element: m_players) {
    if (element.player != nullptr)
      GET_FACTORY->DestroyObject(element.player);
  }
  m_playerCount = 0;
  m_players = {};

  GET_FACTORY->DestroyObject(m_cameraFollow);
  m_cameraFollow = nullptr;
  m_currentGameScene = nullptr;

  m_started = false;

  GET_AUDIO->StopEvent("event:/Music/MainMusic");
}

void game::GameplayManager::StartGame(const std::string& sceneName) {
  if (m_started)
    return;

  m_uninitializeGame =false;

  m_experience = 0;

  SetActive(true);
  UpdateCurrentGameScene();
  m_gameHud->Enable();
  m_gameHud->m_fadeScreen->DoIntermission(sceneName);
  m_cameraFollow = GET_FACTORY->CreateObject<Sigma::CameraFollow>("Main Camera Follow");
  m_cameraFollow->size = 3;
  GET_CAMERA->SetCurrentCamera(m_cameraFollow);

  
  GET_AUDIO->PlayEvent("event:/Music/MainMusic");
}

void game::GameplayManager::GiveXP(int xp) {
  m_experience += xp;
  m_gameHud->UpdateXP(m_experience);
}

void game::GameplayManager::storeScore() {
  if (m_scoreJson.empty())
    return;

  std::fstream rfile(m_scoreJson);

  if (!rfile.is_open()) {
    std::cout << "[GameScene] " << GetName() << " failed to open JSON file " << m_scoreJson << '\n';
    return;
  }

  std::cout << "[GameScene] " << GetName() << " Loading JSON file: " << m_scoreJson << '\n';
  Sigma::json_t rJ = Sigma::json_t::parse(rfile);

  int topScore = rJ["topScore"];

  rJ.clear();
  rfile.close();

  std::ofstream wfile(m_scoreJson);

  Sigma::json_t wJ;
  wJ["topScore"] = topScore<m_experience?m_experience:topScore;
  wJ["playerScore"] = m_experience;

  wfile << wJ;
  wJ.clear();
  wfile.close();

  std::cout << "[GameScene] " << GetName() << " JSON file loaded\n";
}