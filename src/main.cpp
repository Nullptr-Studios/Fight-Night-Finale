/**
 * @file main.cpp
 * @author Xein
 * @date 1/29/2025
 */

#include <aecore/AEEngine.h>
#include "GameManager.hpp"

//SCENES
#include "UI/MainMenu.hpp"

int main() {
  std::unique_ptr<Sigma::GameManager> gameManager = std::make_unique<Sigma::GameManager>("Game", 800, 600);
  auto mainMenu = new game::MainMenu("Main Menu", 0);
  
  gameManager->LoadScene(mainMenu);


  AEGfxSetFullscreen(false);
  while (AESysWindowExists()) {
    gameManager->Run();
  }

  gameManager->Uninitialize();
  AESysExit();

  return 0;
}
