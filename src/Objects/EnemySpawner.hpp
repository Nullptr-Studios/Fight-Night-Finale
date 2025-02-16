//
// Created by Dario on 15/02/2025.
//

#pragma once
#include "Objects/Object.hpp"
#include "glm/vec2.hpp"

namespace game {
class PrototypeScene;
}
namespace game {

struct EnemySpawnData {
  int id;
  glm::vec2 position;
  int entranceId;
};

class EnemySpawner : public Sigma::Object {
public:
  explicit EnemySpawner(uint32_t id) : Object(id) {}
  explicit EnemySpawner(uint32_t id, int activationDistance) : Object(id), m_activationDistance(activationDistance) {}

  void Init() override;
  void Start() override;
  void Update(double deltaTime) override;

  void AddEnemiesData(EnemySpawnData &enemies) { m_spawnData.emplace_back(enemies); }

private:

  bool m_enabled = true;
  
  int m_activationDistance = 0;

  std::vector<EnemySpawnData> m_spawnData;

  std::list<Object*> m_players;

  game::PrototypeScene* m_scene; 
};

}



