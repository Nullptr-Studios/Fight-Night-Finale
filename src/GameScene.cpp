//
// Created by dariormt on 07/02/2025.
//

#include "GameScene.hpp"

#include "Factory.hpp"
#include "Polygon.hpp"
#include "Objects/EnemySpawner.hpp"
#include "Player/Player.hpp"
#include "Controller/CameraController.hpp"
#include "Objects/CameraFollow.hpp"
#include "Scene.hpp"
#include "Tutorial/GlowArea.hpp"
#include "pch.hpp"


void game::GameScene::Load() {
  Sigma::Scene::Load();
  if (m_jsonPath.empty())
    return;

  std::fstream file(m_jsonPath);

  if (!file.is_open()) {
    std::cout << "[GameScene] " << GetName() << " failed to open JSON file " << m_jsonPath << '\n';
    return;
  }

  std::cout << "[GameScene] " << GetName() << " Loading JSON file: " << m_jsonPath << '\n';

  Sigma::json_t J = Sigma::json_t::parse(file);

  file.close();

  m_playerStartPos = {J["playerStart"]["x"], J["playerStart"]["y"]};

  if (J.contains("exitLoc")) {
    m_exitLocation = GET_FACTORY->CreateObject<GlowArea>("Exit");
    m_exitLocation->transform.position = {J["exitLoc"]["x"], J["exitLoc"]["y"], -J["exitLoc"]["y"].get<int>()};
    m_exitLocation->SetActive(false);
    AddChild(m_exitLocation);
  }

  m_sceneBounds.reserve(J["bounds"].size());

  for (auto &boundCoords: J["bounds"]) {
    glm::vec2 bound = {boundCoords["x"], boundCoords["y"]};
    m_sceneBounds.emplace_back(bound);

    if (m_debug) {
      auto point = GET_FACTORY->CreateObject<Sigma::Actor>("Point");
      point->transform.position.x = bound.x;
      point->transform.position.y = bound.y;
      point->transform.position.z = 1000;
      point->transform.scale = {10, 10};
      point->SetTint({0.0f, 1.0f, 1.0f, 1.0f});
      AddChild(point);
    }
  }

  m_enemySpawners.reserve(J["enemySpawners"].size());

  for (auto &spawners: J["enemySpawners"]) {

    game::EnemySpawner* s;
    if (spawners.contains("required"))
      s = GET_FACTORY->CreateObject<EnemySpawner>(spawners["name"], spawners["activationRange"], m_enemySpawners[spawners["required"]]);
    else
      s = GET_FACTORY->CreateObject<EnemySpawner>(spawners["name"], spawners["activationRange"]);

    s->transform.position = {spawners["pos"]["x"], spawners["pos"]["y"], -spawners["pos"]["y"].get<int>()};
    

    for (auto &enemies: spawners["enemies"]) {
      EnemySpawnData data{};
      data.id = enemies["id"];
      data.position = {enemies["pos"]["x"], enemies["pos"]["y"]};

      //TODO: Utilize entrance ID
      data.entranceId = enemies["entranceId"];

      if(enemies.contains("stepAmmount"))
        data.stepAmmount = enemies["stepAmmount"];
      else
        data.stepAmmount = 1;

      if(enemies.contains("delayTime"))
        data.delayTime = enemies["delayTime"];
      else
        data.delayTime = spawners.contains("delayTime") ? spawners["delayTime"].get<float>() : .5f;  ///<< Default wait value
      s->AddEnemiesData(data);
    }

    m_enemySpawners.push_back(s);
  }

  std::cout << "[GameScene] " << GetName() << " JSON file loaded\n";

  J.clear();

  m_sceneBoundsPoly = new Sigma::Polygon(m_sceneBounds);
  
}

void game::GameScene::Update(double delta){
  Sigma::Scene::Update(delta);

  int spawnercount = 0;
  for(auto enemyspawner : m_enemySpawners) {
   if(enemyspawner->GetFinished())
     spawnercount++;
  }

  if (spawnercount >= m_enemySpawners.size() && !m_isSceneFinished) {
    if (m_exitLocation)
      m_exitLocation->SetActive(true);
    m_isSceneFinished = true;
  }
}

void game::GameScene::Unload() {
  Scene::Unload();

  for (auto spawner: m_enemySpawners) {
    GET_FACTORY->DestroyObject(spawner);
  }

  delete m_sceneBoundsPoly;
}
void game::GameScene::DebugWindow() {
  Scene::DebugWindow();
  
  ImGui::Checkbox("Debug draw", &m_debug);
}
