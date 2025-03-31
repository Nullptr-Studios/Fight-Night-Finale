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
  explicit Box(Sigma::id_t id, const char* texture = "assets/objects/SlotMachine_0.png",
                const char* brokenTexture = "assets/objects/SlotMachine_1.png",
                const char * pickupTexture = "assets/objects/Hamburger.png") : Damageable(id),
                m_texture(texture), m_brokenTexture(brokenTexture), m_pickupTexture(pickupTexture) {};
  ~Box() override = default;

  void Init() override;
  void Update(double deltaTime) override;
  void OnDed() override;
  void Destroy() override;

  //Setters
  void setSize(glm::vec3 size) {m_size = size;}
  void setPickupSize(glm::vec3 size) {m_pickupSize = size;}
  void setHealAmount (float heal) {m_pickupHeal = heal;}

  glm::mat3 *GetTextureTransform() override {
    m_tMtx = m_animComp->GetTextureMatrix();
    return &m_tMtx;
  }

protected:

  std::shared_ptr<Object> m_pickup = nullptr; ///>@brief pickup object
  //Box
  const char * m_texture; ///>@brief box texture
  const char * m_brokenTexture; ///>@brief box broken texture
  glm::vec3 m_size = {32,73,64}; ///>@brief box size
  //Pickup
  const char * m_pickupTexture; ///>@brief pickup texture
  glm::vec3 m_pickupSize = {16, 16, 32}; ///>@brief pickup size
  float m_pickupHeal = 50; ///>@brief pickup heal amount
  
};
}
