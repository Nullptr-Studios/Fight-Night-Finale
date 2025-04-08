//
// Created by Dario on 15/02/2025.
//

#include "EnemySpawner.hpp"
#include "Enemies/BigEnemy.hpp"
#include "Enemies/DefaultEnemy.hpp"
#include "Enemies/GrabEnemy.hpp"
#include "Enemies/TntEnemy.hpp"
#include "Enemies/Boss.hpp"
#include "GameScene.hpp"
#include "Manager/GameplayManager.hpp"

void game::EnemySpawner::Init() {
  Object::Init();
  m_gameplayManager = GameplayManager::GetInstance();
}

void game::EnemySpawner::Start() { Object::Start(); }

void game::EnemySpawner::SpawnEnemy() {
  std::shared_ptr<Enemy> e;

  switch (m_currentEnemyData.id) {
    default:
    case 0:
      e = GET_FACTORY->CreateObject<game::DefaultEnemy>("Basic Enemy", "assets/characters/BasicEnemy/behaviour.json");
    break;
    case 1:
      e = GET_FACTORY->CreateObject<game::GrabEnemy>("Grab Enemy", "assets/characters/grabEnemy/behaviour.json");
    break;
    case 2:
      e = GET_FACTORY->CreateObject<game::BigEnemy>("Big Enemy", "assets/characters/bigEnemy/behaviour.json");
    break;
    case 3:
      e = GET_FACTORY->CreateObject<game::TntEnemy>("TNT Enemy", "assets/characters/tntEnemy/behaviour.json");
    break;
    case 4:
      e = GET_FACTORY->CreateObject<game::Boss>("The Presenter Enemy", "assets/characters/presenter/behaviour.json");
    break;
  }

  e->transform.position.x = m_currentEnemyData.position.x;
  e->transform.position.y = m_currentEnemyData.position.y;
  e->transform.scale = {32.0f, 64.0f};
  e->Enable(m_gameplayManager->GetPlayers());
  e->SetSceneBoundsPoly(m_gameplayManager->GetSceneBoundsPoly());
  m_enemies.push_back(e);
}

void game::EnemySpawner::Update(double deltaTime) {
  Object::Update(deltaTime);

  if (m_finished)
    return;

  if (m_requiredSpawner)
    m_enabled = m_requiredSpawner->GetFinished();
  else
    m_enabled = true;

  if (!m_enabled)
    return;

  if (!m_triggered) {

    for (auto &ps: *m_gameplayManager->GetPlayers()) {
      if (!ps.player)
        continue;

      if (!ps.player->GetAlive())
        continue;

      float distance = glm::distance(ps.player->transform.position, transform.position);
      if (distance < m_activationDistance) {
        m_triggered = true;
        m_spawnTimer = m_spawnData[m_currentEnemyIndex].delayTime;
        return;
      }
    }
  } else if (!m_spawned) {
    m_spawnTimer += deltaTime;

    if (m_currentEnemyIndex >= m_spawnData.size()) {
      m_spawned = true;
      return;
    }

    if (m_spawnTimer >= m_spawnData[m_currentEnemyIndex].delayTime) {
      m_spawnTimer = 0.0f;


      int stepAmount = m_spawnData[m_currentEnemyIndex].stepAmmount;

      for (int i = 0; i < stepAmount && m_currentEnemyIndex < m_spawnData.size(); ++i) {
        m_currentEnemyData = m_spawnData[m_currentEnemyIndex];
        SpawnEnemy();
        if (!m_spawnerDoors.empty() && m_currentEnemyData.entranceId < m_spawnerDoors.size()) {
          m_spawnerDoors[m_currentEnemyData.entranceId]->Open(0.75f);
        }

        m_currentEnemyIndex++;
      }
    }
  }


  if (!m_spawned)
    return;

  // TODO: this must be changed whenever the death state is done
  short deletedAmmount = 0;
  for (auto enemy: m_enemies) {
    if (enemy) {
      if (enemy->GetHealth() <= 0) {
        deletedAmmount++;
      }
    }
  }
  if (deletedAmmount == m_enemies.size()) {
    m_finished = true;
    m_enabled = false;
    game::GameplayManager::GetInstance()->FinishedAnSpawner();
  }
}

void game::EnemySpawner::Destroy() {
  Object::Destroy();

  for (auto enemy: m_enemies) {
    GET_FACTORY->DestroyObject(enemy);
  }
  m_enemies.clear();
}
