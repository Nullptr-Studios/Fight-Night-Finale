//
// Created by dariormt on 08/02/2025.
//

#pragma once

#include "Objects/Damageable.hpp"

namespace game {
class PunchingBag : public Sigma::Damageable {
  
public:
  explicit PunchingBag(Sigma::id_t id) : Damageable(id) {}
  ~PunchingBag() override = default;
  
  void Init() override;
  void Update(double delta) override;

  void OnDamage(const Sigma::Damage::DamageEvent &e) override;

  glm::mat3 *GetTextureTransform() override;
private:
  Actor* m_debugCol;
};
}



