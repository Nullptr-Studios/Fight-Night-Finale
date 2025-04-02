//
// Created by Dario on 03/03/2025.
//

#pragma once

#include "../../GameScene.hpp"
#include "Objects/Object.hpp"

namespace Sigma {
class Polygon;
class CameraFollow;
}

namespace game {
class HUD;
class GameScene;
class Player;
class HealthBar;

struct PlayerStruct {
  std::shared_ptr<Player> player = nullptr;
  std::shared_ptr<HealthBar> healthBar = nullptr;
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
  void FirstUpdate(double deltaTime) override;
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

  void SetPlayerAsDead(Object* player);


  /**
   * @brief Check if the second player wants to join the game
   */
  void CheckForCoop();

  #pragma region Scene

  void OnScenePass();

  void TeleportPlayersToNextScene();

/**
   * @brief Update the current game scene pointer
   */
  void UpdateCurrentGameScene();

  /**
   * @brief Go to the next scene
   */
  void GotoNextScene();

  /**
   * @brief Next scene logic after a frame
   */
  void GotoNextSceneAfter();

  Sigma::Polygon* GetSceneBoundsPoly() { return m_currentGameScene->GetSceneBoundsPoly(); }

  #pragma endregion

  
  void FinishedAnSpawner();



  void UninitializeGame();

  void StartGame(const std::string& sceneName = "Level 1");

  std::array<PlayerStruct, 2> *GetPlayers() { return &m_players; }

  static GameplayManager* GetInstance() { return m_instance; }

  #pragma region HUD
  void EnableHUD();

  void DisableHUD();
  
  void GiveXP(int xp);

  [[nodiscard]] int GetXP() const { return m_experience; }

  
  #pragma endregion

private:
  static GameplayManager* m_instance;
  std::shared_ptr<Sigma::CameraFollow> m_cameraFollow{};

  std::shared_ptr<HUD> m_gameHud = nullptr;

  /**
   * @brief holds the information required for the players
   */
  std::array<PlayerStruct, 2> m_players = {};
  game::GameScene *m_currentGameScene = nullptr;
  unsigned char m_playerCount = 0;
  bool m_gameSceneIsDirty = true;

  /**
   * @brief holds the information required for the xp system
   */
  int m_experience = 0;
  bool m_started = false;
};
}



