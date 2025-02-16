/**
 * @file PlayButton.hpp
 * @author dante
 * @date 2/13/2025
 *
 * @brief A button that will switch scenes
 */
#pragma once
#include "UI/UIButton.hpp"
namespace game {
class PlayButton final : public Sigma::UIButton {
public:
  explicit PlayButton(const Sigma::id_t id) : UIButton(id) {}

  void OnClick() override;

  void OnHoverStart() override;

  void OnHoverExit() override;
};

} // namespace game
