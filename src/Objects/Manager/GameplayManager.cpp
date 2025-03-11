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
#include "UI/HealthBar.hpp"

game::GameplayManager* game::GameplayManager::m_instance = nullptr;

void game::GameplayManager::Init() {
  Object::Init();

#ifdef DEBUG_CAMERA
  GET_CAMERA->SetCurrentCamera(GET_FACTORY->CreateObject<Sigma::Camera>("Debug Camera"));
  GET_CAMERA->GetCurrentCamera()->size = 1;
#else
  m_cameraFollow = GET_FACTORY->CreateObject<Sigma::CameraFollow>("Main Camera Follow");
  m_cameraFollow->size = 2;
  GET_CAMERA->SetCurrentCamera(m_cameraFollow);
#endif


  m_gameHud = GET_FACTORY->CreateObject<game::HUD>("Game HUD");
  
  
}
void game::GameplayManager::Start() {
  Object::Start();
  UpdateCurrentGameScene();
}

void game::GameplayManager::Update(double deltaTime) {
  Object::Update(deltaTime);

  // Update the current game scene, and for now teleport players FIXME: this should be done in another way
  if (m_gameSceneIsDirty) {
    GotoNextSceneAfter();
  }

  if (!m_playerCount && AEInputGamepadButtonPressed(0, AE_GAMEPAD_START)) {
    InitPlayer(0);
  } else if (!m_playerCount && AEInputKeyPressed(' ')) {
     InitPlayer(-1);
  }
  CheckForCoop();

  // Debug pass level
  if (AEInputKeyTriggered('P')) {
    GotoNextScene();
  }
  
}


void game::GameplayManager::RespawnPlayer(game::Player *player) {
  if (m_currentGameScene)
    player->transform.position = {m_currentGameScene->GetPlayerStartPos().x, m_currentGameScene->GetPlayerStartPos().y,
                                  -m_currentGameScene->GetPlayerStartPos().y};
}

void game::GameplayManager::TeleportPlayersToNextScene() {
  for (auto ps: m_players) {
    if (ps.player) {
      RespawnPlayer(ps.player);
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
    m_cameraFollow->m_targetP1 = p.player;
  else
    m_cameraFollow->m_targetP2 = p.player;

  RespawnPlayer(p.player);
  
  p.player->SetSceneBoundsPoly(m_currentGameScene->GetSceneBoundsPoly());
  
  
  m_playerCount++;
}

void game::GameplayManager::CheckForCoop() {
  // If pressed key 2 create 2nd player
  if (m_playerCount == 2 || m_playerCount == 0)
      return;
  if (m_players[0].player->GetControllerID() <= -1 && AEInputGamepadButtonTriggered(0, AE_GAMEPAD_START)) {
    InitPlayer(0);
    RespawnPlayer(m_players[1].player);
  } else if (AEInputGamepadButtonTriggered(1, AE_GAMEPAD_START)) {
    InitPlayer(1);
    RespawnPlayer(m_players[1].player);
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
  m_cameraFollow->transform.position.x = m_players[0].player->transform.position.x;
  m_cameraFollow->transform.position.y = m_players[0].player->transform.position.y;
}


void game::GameplayManager::FinishedAnSpawner(){
  m_gameHud->EnableGOIndicator();
}



