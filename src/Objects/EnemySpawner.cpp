//
// Created by Dario on 15/02/2025.
//

#include "EnemySpawner.hpp"
#include "Enemies/DefaultEnemy.hpp"
#include "GameManager.hpp"
#include "PrototypeScene.hpp"

// FIXME: this will only work for the first player and the prototype scene
void game::EnemySpawner::Init() {
  Object::Init();
  m_scene = dynamic_cast<game::PrototypeScene*>(GET_SCENE(0));
}

void game::EnemySpawner::Start()
{
  Object::Start();
 
}

void game::EnemySpawner::Update(double deltaTime) {
  Object::Update(deltaTime);

  if (!m_enabled)
    return;

  for (auto player: m_scene->m_players) {
    if (!player) continue;

    float distance = glm::distance(player->transform.position, transform.position);
    if (distance < m_activationDistance) {
      for (auto &enemy: m_spawnData) {
        auto e = GET_FACTORY->CreateObject<game::DefaultEnemy>("Enemy", "assets/characters/enemy/behaviour.json");
        e->transform.position.x = enemy.position.x;
        e->transform.position.y = enemy.position.y;
        e->transform.scale = {32.0f, 64.0f};
        e->Enable(&m_scene->m_players);
        m_enemies.push_back(e);
      }
      m_enabled = false;
      return;
    }
  }
}
void game::EnemySpawner::Destroy() {
  Object::Destroy();

  for (auto enemy: m_enemies) {
    GET_FACTORY->DestroyObject(enemy);
  }
}
