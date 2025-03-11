//
// Created by Dario on 03/03/2025.
//

#pragma once

#include "GameScene.hpp"
#include "Objects/Object.hpp"

namespace Sigma {
class Polygon;
class CameraFollow;
}

namespace game {
class GameScene;
class Player;
class HealthBar;
class HUD;

struct PlayerStruct {
  Player* player = nullptr;
  HealthBar* healthBar = nullptr;
};

/**
 * @class GameplayManager
 * @brief Global gameplay manager that handles everything related to the gameplay, such as the camera, player, enemies,
 * etc.
 * @brief This is a permanent object that will be created at the start of the game and will be destroyed at the end.
 */
class GameplayManager : public Sigma::Object
{
public:
  explicit GameplayManager(uint32_t id) : Object(id) { m_instance = this; }
  ~GameplayManager() override { m_instance = nullptr; };

  void Init() override;
  void Start() override;
  void Update(double deltaTime) override;
  //void DebugWindow() override;

  /**
   * @brief TODO: This should call a cool screen effect like a fade in or something cool (STAGE 1) in cool letters and animation or something cool :)
   */
  //void InitScreen();

  /**
   * @brief Initialize the player to its default state
   * @param playerID
   */
  void InitPlayer(unsigned controllerID);

  /**
   * @brief Respawn the player
   */
  void RespawnPlayer(game::Player* player);

  void TeleportPlayersToNextScene();

  /**
   * @brief Check if the second player wants to join the game
   */
  void CheckForCoop();

  void UpdateCurrentGameScene();

  void GotoNextScene();

  void GotoNextSceneAfter();

  void FinishedAnSpawner();

  std::array<PlayerStruct, 2> *GetPlayers() { return &m_players; }

  Sigma::Polygon* GetSceneBoundsPoly() { return m_currentGameScene->GetSceneBoundsPoly(); }

  static GameplayManager* GetInstance() { return m_instance; }

private:
  static GameplayManager* m_instance;
  //bool m_gameStarted = false;
  Sigma::CameraFollow* m_cameraFollow;

  HUD* m_gameHud = nullptr;

  /**
   * @brief holds the information required for the players
   */
  std::array<PlayerStruct, 2> m_players = {};
  unsigned char m_playerCount = 0;
  game::GameScene* m_currentGameScene = nullptr;
  bool m_gameSceneIsDirty = true;
};
}



