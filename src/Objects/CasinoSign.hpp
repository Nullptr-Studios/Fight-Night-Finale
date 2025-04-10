//
// Created by Xein on 4/9/2025.
//

#ifndef CASINOSIGN_HPP
#define CASINOSIGN_HPP

#include "Objects/Actor.hpp"

namespace game {

class CasinoSign : public Sigma::Actor {
public:
  explicit CasinoSign(Sigma::id_t id);
  glm::mat3 *GetTextureTransform() override;
};

} // game

#endif //CASINOSIGN_HPP
