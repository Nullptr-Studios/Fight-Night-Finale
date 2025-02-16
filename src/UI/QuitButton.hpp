/**
 * @file QuitButton.hpp
 * @author dante
 * @date 2/13/2025
 *
 * @brief A button that will quit the game
 */
#pragma once
#include "UI/UIButton.hpp"
namespace game {
class QuitButton final : public Sigma::UIButton {
public:
  explicit QuitButton(const Sigma::id_t id) : UIButton(id) {}

  void OnClick() override;

  void OnHoverStart() override;

  void OnHoverExit() override;
};

} // namespace game
