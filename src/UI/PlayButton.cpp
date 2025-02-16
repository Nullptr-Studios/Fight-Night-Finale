#include "PlayButton.hpp"
#include "../PrototypeScene.hpp"
#include "GameManager.hpp"
namespace game {

void PlayButton::OnClick() {
  UIButton::OnClick();
  std::cout << "Changing Scene from MainMenu to Game\n";
  auto s = new game::PrototypeScene("Game", 1,"assets/prototype-scene/ProtoScene.json");
  GET_MANAGER->LoadScene(s);
}
void PlayButton::OnHoverStart() {
  UIButton::OnHoverStart();
  transform.scale *= 1.05;
}
void PlayButton::OnHoverExit() {
  UIButton::OnHoverExit();
  transform.scale /= 1.05;
}
} // namespace FNFE
