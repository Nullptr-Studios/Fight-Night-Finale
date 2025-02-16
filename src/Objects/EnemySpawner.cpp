//
// Created by Dario on 15/02/2025.
//

#include "EnemySpawner.hpp"

#include "GameManager.hpp"
#include "PrototypeScene.hpp"

// FIXME: this will only work for the first player and the prototype scene
void game::EnemySpawner::Init() {
  Object::Init();
  auto s = dynamic_cast<game::PrototypeScene*>(GET_SCENE(0));
}

void game::EnemySpawner::Start()
{
  Object::Start();
  
}

void game::EnemySpawner::Update(double deltaTime) {
  Object::Update(deltaTime);
  
}
