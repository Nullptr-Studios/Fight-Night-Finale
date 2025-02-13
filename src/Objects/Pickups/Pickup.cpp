//
// Created by cmgbp on 13/02/2025.
//

#include "Pickup.hpp"

namespace game {

bool Pickup:: OnCollision(Sigma::Collision::CollisionEvent &e) override {
  if (auto player = dynamic_cast<Player*>(e.GetOther())) {
    player->OnHeal(50);
    SetActive(false);
    return true;
  }
  return false;
}

}