/**
 * @file main.cpp
 * @author Xein
 * @date 1/29/2025
 */

#include <aecore/AEEngine.h>
#include "GameManager.hpp"

//SCENES
#include "Level1/Scene1.hpp"
#include "Level1/Scene2.hpp"
#include "Level1/Scene3.hpp"
#include "Level1/Scene4.hpp"
#include "Level1/Scene5.hpp"
#include "Level1/Scene6.hpp"
#include "Level1/Scene7.hpp"

int main() {
  std::unique_ptr<Sigma::GameManager> gameManager = std::make_unique<Sigma::GameManager>("Game", 800, 600);
  auto scene1 = new game::Scene1("Scene1", 1, "assets/level-1/scene-1.json");
  auto scene2 = new game::Scene2("Scene2", 2, "assets/level-1/scene-2.json");
  auto scene3 = new game::Scene3("Scene3", 3, "assets/level-1/scene-3.json");
  auto scene4 = new game::Scene4("Scene4", 4, "assets/level-1/scene-4.json");
  auto scene5 = new game::Scene5("Scene5", 5, "assets/level-1/scene-5.json");
  auto scene6 = new game::Scene6("Scene6", 6, "assets/level-1/scene-6.json");
  auto scene7 = new game::Scene7("Scene7", 7, "assets/level-1/scene-7.json");
  gameManager->LoadScene(scene3);

  AEGfxSetFullscreen(false);
  while (AESysWindowExists()) {
    gameManager->Run();
  }

  gameManager->Uninitialize();
  AESysExit();

  return 0;
}
