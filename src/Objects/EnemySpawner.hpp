//
// Created by Dario on 15/02/2025.
//

#pragma once
#include "Objects/Object.hpp"

namespace game {
class Enemy;
}
namespace game {
class GameplayManager;
class GameScene;
class PrototypeScene;


struct EnemySpawnData {
  int id;
  glm::vec2 position;
  int entranceId;
};

class EnemySpawner : public Sigma::Object {
public:
  explicit EnemySpawner(uint32_t id) : Object(id) {}
  explicit EnemySpawner(uint32_t id, int activationDistance, EnemySpawner* requiredSpawner = nullptr) : Object(id), m_activationDistance(activationDistance), m_requiredSpawner(requiredSpawner) {}

  void Init() override;
  void Start() override;
  void Update(double deltaTime) override;

  void Destroy() override;

  void SetEnabled(bool enabled) {m_enabled = enabled;} 

  // short GetRequiredId() {return m_requiredId;}

  [[nodiscard]] bool GetFinished() const {return m_finished;}
  void AddEnemiesData(EnemySpawnData &enemies) { m_spawnData.emplace_back(enemies); }

private:

  EnemySpawner* m_requiredSpawner = nullptr;

  bool m_finished = false;

  bool m_enabled = false;

  bool m_spawned = false;
  
  int m_activationDistance = 0;

  std::vector<EnemySpawnData> m_spawnData;

  std::list<Object*> m_players;

  std::list<Enemy*> m_enemies;

  GameplayManager* m_gameplayManager = nullptr;
  
};

}



