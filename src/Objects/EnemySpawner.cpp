//
// Created by Dario on 15/02/2025.
//

#include "EnemySpawner.hpp"
#include "Enemies/DefaultEnemy.hpp"
#include "GameScene.hpp"
#include "Manager/GameplayManager.hpp"

void game::EnemySpawner::Init() {
  Object::Init();
  m_gameplayManager = GameplayManager::GetInstance();
}

void game::EnemySpawner::Start() { Object::Start(); }

void game::EnemySpawner::SpawnEnemy() {
  auto e = GET_FACTORY->CreateObject<game::DefaultEnemy>("Enemy", "assets/characters/BasicEnemy/behaviour.json");
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
  }
}
void game::EnemySpawner::Destroy() {
  Object::Destroy();

  for (auto enemy: m_enemies) {
    GET_FACTORY->DestroyObject(enemy);
  }
}
