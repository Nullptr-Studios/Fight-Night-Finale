#include "QuitButton.hpp"

namespace game {
void QuitButton::OnClick() {
  UIButton::OnClick();
  std::cout << "Quiting Game\n";
  AESysExit();
}

void QuitButton::OnHoverStart() {
  UIButton::OnHoverStart();
  transform.scale *= 1.05;
}

void QuitButton::OnHoverExit() {
  UIButton::OnHoverExit();
  transform.scale /= 1.05;
}
} // namespace game
