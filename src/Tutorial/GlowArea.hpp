/**
 * @file GlowArea.hpp
 * @author Xein
 * @date 11/03/25
 *
 * @brief [TODO: Brief description of the file's purpose]
 */
#pragma once
#include "Core.hpp"
#include "Objects/Actor.hpp"
#include "GameScene.hpp"

namespace game{

class GlowArea : public Sigma::Actor {
public:
  explicit GlowArea(const Sigma::id_t id) : Actor(id) {}

  void Init() override;
  bool OnCollision(Sigma::Collision::CollisionEvent& e) override;

  void SetNextScene(GameScene* scene) { m_scene = scene; }
  void SetCurrentScene(const std::string& name) { m_current = name; }

private:
  GameScene* m_scene = nullptr;
  bool m_player1 = false;
  bool m_player2 = false;
  char m_playerCount = 1;
  std::string m_current;
};

}

