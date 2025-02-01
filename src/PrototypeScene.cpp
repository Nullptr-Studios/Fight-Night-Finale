#include "PrototypeScene.hpp"
#include "Core.hpp"
#include "Factory.hpp"
#include "Player/Player.hpp"
#include "TestCollision.hpp"

void game::PrototypeScene::Load() {
  Scene::Load();
  GET_FACTORY->CreateObject<Player>("Player");
  // GET_FACTORY->CreateObject<TestCollision>("Test Collision");
}

void game::PrototypeScene::Update(double delta) {
  Scene::Update(delta);
}

void game::PrototypeScene::Draw() {
  Scene::Draw();
}
