/**
 * @file Box.hpp
 * @author Alexey
 * @date 15/02/2025
 *
 * @brief class for a destructible box
 */

#pragma once
#include "Objects/Damageable.hpp"

namespace game {
class Box: public Sigma::Damageable {
  public:
    explicit Box(Sigma::id_t id, const char* boxJsonPath, const char* pickupJsonPath) :
    Damageable(id), m_jsonPath(boxJsonPath), m_pickupJsonPath(pickupJsonPath) {};
    ~Box() override = default;

  void Init() override;
  void OnDed() override;

protected:
  //Box
  std::string m_jsonPath; ///>@brief box json path
  std::string m_texture; ///>@brief box texture
  std::string m_brokenTexture; ///>@brief box broken texture
  glm::vec3 m_size; ///>@brief box size
  //Pickup
  std::string m_pickupJsonPath; ///>@brief pickup json path
  std::string m_pickupTexture; ///>@brief pickup texture
  glm::vec3 m_pickupSize; ///>@brief pickup size
  float m_pickupHeal; ///>@brief pickup heal amount
};
}