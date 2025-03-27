/**
 * @file Tnt.hpp
 * @author Dante Harper
 * @date 11/03/25
 *
 * @brief BOOM BOOM IMA GO BOOM YAY
 */
#pragma once

#include "Collision/OneHitCollider.hpp"
#include "Objects/Actor.hpp"
#include "Objects/Character.hpp"
namespace game {
class Tnt : public Sigma::Actor {
public:
  explicit Tnt(Sigma::id_t id) : Actor(id) {}
  void Init() override;
  void Update(double delta) override;
  void DebugWindow() override;
  void Destroy() override;
  float m_length{};
  float m_timer = 0;
  bool boom = false;
  glm::vec3 m_boomBox{};
  glm::vec2 m_powBox{};
  float m_damage{};
  glm::vec3 m_start{};
  glm::vec3 m_target{};
  std::shared_ptr<Sigma::Collision::OneHitCollider> m_attackCollider{};
private:
};
}


