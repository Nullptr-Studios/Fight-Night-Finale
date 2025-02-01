#include "PrototypeScene.hpp"
#include "Factory.hpp"
#include "Objects/Character.hpp"
#include "Player/Player.hpp"
#include "core.hpp"

void game::PrototypeScene::Load() {
  Scene::Load();
  FNFE_FACTORY->CreateObject<Player>("Player");
}

void game::PrototypeScene::Update(double delta) {
  Scene::Update(delta);
}

void game::PrototypeScene::Draw() {
  Scene::Draw();
}
