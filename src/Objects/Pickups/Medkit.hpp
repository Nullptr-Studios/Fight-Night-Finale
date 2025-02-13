//
// Created by Alexey on 11/02/2025.
//

#pragma once
#include "Pickup.hpp"

namespace game {
class Medkit: Pickup {
  public:
    explicit Medkit(Sigma::id_t id) : Pickup(id) {
      m_healAmount = 50.0f;
    };
    ~Medkit() override = default;

};
}
