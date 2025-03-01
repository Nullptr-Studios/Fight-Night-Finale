/**
 * @file main.cpp
 * @author Xein
 * @date 1/29/2025
 */

#include <aecore/AEEngine.h>
#include "GameManager.hpp"
#include "Testing_Scene.hpp"
#include "UI/MainMenu.hpp"
#include "PrototypeScene.hpp"

//SCENES
#include "level1/Scene1.hpp"
#include "level1/Scene2.hpp"
#include "level1/Scene3.hpp"
#include "level1/Scene4.hpp"
#include "level1/Scene5.hpp"
#include "level1/Scene6.hpp"
#include "level1/Scene7.hpp"

int main() {
  std::unique_ptr<Sigma::GameManager> gameManager = std::make_unique<Sigma::GameManager>("Game", 800, 600);
  auto scene = new game::Scene7("Cornelius Coconut", 69, "assets/level-1/scene-7.json");
  gameManager->LoadScene(scene);

  AEGfxSetFullscreen(false);
  while (AESysWindowExists()) {
    gameManager->Run();
  }

  gameManager->Uninitialize();
  AESysExit();

  return 0;
}
