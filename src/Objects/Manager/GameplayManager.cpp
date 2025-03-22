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

  /*GET_AUDIO->LoadBank("assets/Sound/Desktop/Master.bank");
  GET_AUDIO->LoadBank("assets/Sound/Desktop/Master.strings.bank");
  GET_AUDIO->LoadBank("assets/Sound/Desktop/Music.bank");
  GET_AUDIO->LoadEvent("event:/Music/TestMusic");*/
  

}
void game::GameplayManager::Start() {
  Object::Start();
  StartGame();
  
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
  for (auto element: m_players) {
    if (element.player == nullptr)
      continue;
    
    if (!element.player->IsActive()) {
      dedPlayers++;
    }
  }
  
  if (dedPlayers >= m_playerCount && m_playerCount != 0) {
    GET_MANAGER->LoadScene(new DeadScene("Dead Scene", 0));
    GET_MANAGER->UnloadScene(m_currentGameScene->GetID());
    UninitializeGame();
  }

  //return to main menu
  if (AEInputKeyPressed(27)) {
    GET_MANAGER->LoadScene(new MainMenu("Main Menu", 0));
    GET_MANAGER->UnloadScene(m_currentGameScene->GetID());
    UninitializeGame();
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
  /*player->SetTint(glm::vec4(1));
  player->SetAlive(true);
  player->ResetHealth();
  player->SetActive(true);
  player->m_animComp->SetCurrentAnim("Idle");
  player->m_animComp->PlayAnim();*/
}

void game::GameplayManager::TeleportPlayersToNextScene() {
  for (auto ps: m_players) {
    if (ps.player) {
      RespawnPlayer(ps.player.get());
      ps.player->SetSceneBoundsPoly(m_currentGameScene->GetSceneBoundsPoly());
    }
  }
}

void game::GameplayManager::InitPlayer(unsigned controllerID)
{
  PlayerStruct p {};
  p.player = GET_FACTORY->CreateObject<game::Player>("Player", controllerID, "assets/characters/player/behaviour.json");

  // Add player to the array
  m_players[m_playerCount] = p;

  m_gameHud->UpdatePlayerHUD();

  // Setup Camera
  if (m_playerCount == 0) 
    m_cameraFollow->m_targetP1 = p.player.get();
  else
    m_cameraFollow->m_targetP2 = p.player.get();

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
  GET_MANAGER->LoadScene(m_currentGameScene->GetNextScene());
  GET_MANAGER->UnloadScene(m_currentGameScene->GetID());

  //Because the scene is being unloaded at late update wee need to wait till next frame to update the current scene
  m_gameSceneIsDirty = true;
}

void game::GameplayManager::GotoNextSceneAfter() {
  UpdateCurrentGameScene();
  TeleportPlayersToNextScene();
  
  AEDbgAssertFunction(m_players[0].player != nullptr, __FILE__, __LINE__, "m_player[0] is nullptr");
  m_cameraFollow->transform.position.x = m_players[0].player->transform.position.x;
  m_cameraFollow->transform.position.y = m_players[0].player->transform.position.y;
}




void game::GameplayManager::FinishedAnSpawner() { m_gameHud->EnableGOIndicator(); }

void game::GameplayManager::EnableHUD() { m_gameHud->Enable(); }
void game::GameplayManager::DisableHUD() { m_gameHud->Disable(); }

void game::GameplayManager::UninitializeGame() {
  DisableHUD();
  SetActive(false);

  for (auto element: m_players) {
    if (element.player != nullptr)
      GET_FACTORY->DestroyObject(element.player);
  }
  m_playerCount = 0;
  m_players = {};

  GET_FACTORY->DestroyObject(m_cameraFollow);
  m_currentGameScene = nullptr;

  m_started = false;

  GET_AUDIO->StopEvent("event:/Music/TestMusic");
}

void game::GameplayManager::StartGame() {
  if (m_started)
    return;
  
  SetActive(true);
  UpdateCurrentGameScene();
  m_cameraFollow = GET_FACTORY->CreateObject<Sigma::CameraFollow>("Main Camera Follow");
  m_cameraFollow->size = 3;
  GET_CAMERA->SetCurrentCamera(m_cameraFollow);


  //GET_AUDIO->PlayEvent("event:/Music/TestMusic");
}




