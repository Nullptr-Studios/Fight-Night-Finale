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
    explicit Box(Sigma::id_t id) : Damageable(id) {}
    ~Box() override = default;

  void Init() override;
  void OnDed() override;

};
}