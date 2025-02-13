//
// Created by Alexey on 11/02/2025.
//

#pragma once
#include "Objects/Damageable.hpp"

namespace game {
class Box: Sigma::Damageable {
  public:
    explicit Box(Sigma::id_t id) : Damageable(id) {}
    ~Box() override = default;

  //TODO: make OnDed change texture!
  void OnDed() override;
  //TODO: make OnDamage spawn a Pickup item (Medkit)
  void OnDamage(const Sigma::Damage::DamageEvent &e) override;

};
}