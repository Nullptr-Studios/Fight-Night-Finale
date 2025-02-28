/**
 * @file main.cpp
 * @author Xein
 * @date 1/29/2025
 */

#include <aecore/AEEngine.h>
#include "GameManager.hpp"
#include "Testing_Scene.hpp"
#include "UI/MainMenu.hpp"

int main() {
  std::unique_ptr<Sigma::GameManager> gameManager = std::make_unique<Sigma::GameManager>("Game", 800, 600);
  auto scene = new game::Testing_Scene("Prototype", 0, "assets/level-1/scene-4.json");
  gameManager->LoadScene(scene);

  AEGfxSetFullscreen(false);
  while (AESysWindowExists()) {
    gameManager->Run();
  }

  gameManager->Uninitialize();
  AESysExit();

  return 0;
}
