//
// Created by dariormt on 07/02/2025.
//

#pragma once
#include "Scene.hpp"

namespace Sigma {
class Polygon;
}

namespace game {

class EnemySpawner;
class Player;

class GameScene : public Sigma::Scene {
public:
 
  /**
   * @brief Construct a new Game Scene object
   *
   * @param name
   * @param ID
   * @param jsonPath
   */
  GameScene(const char *name, unsigned ID, const char *jsonPath) : Scene(name, ID), m_jsonPath(jsonPath) {};

  void Load() override;
  void Unload() override;
  void DebugWindow() override;

  /**
   * @brief returns the current scene bounds
   * @return Polygon*
   */
  [[nodiscard]] Sigma::Polygon *GetSceneBoundsPoly() const { return m_sceneBoundsPoly; }

  [[nodiscard]] glm::vec2 GetPlayerStartPos() const { return m_playerStartPos; }

  [[nodiscard]] Sigma::Scene *GetNextScene() const { return m_nextScene; }

  void SetNextScene(Sigma::Scene *nextScene) { m_nextScene = nextScene; }

protected:
  bool m_debug = true;

  std::string m_jsonPath{};
  glm::vec2 m_playerStartPos{};
  std::vector<glm::vec2> m_sceneBounds{};
  std::vector<EnemySpawner *> m_enemySpawners{};
  Sigma::Scene * m_nextScene = nullptr;
};

} // namespace game
