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
#include "Tutorial/Tutorial_1.hpp"
#include "Tutorial/Tutorial_2.hpp"
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
