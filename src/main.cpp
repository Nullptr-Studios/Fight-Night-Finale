/**
 * @file main.cpp
 * @author Xein
 * @date 1/29/2025
 */

#include <aecore/AEEngine.h>
#include "GameManager.hpp"
#include "PrototypeScene.hpp"

int main() {
  std::unique_ptr<sigma::GameManager> gameManager = std::make_unique<sigma::GameManager>("Game", 800, 600);

  auto scene = new game::PrototypeScene("PrototypeScene", 1);
  gameManager->LoadScene(scene);

  while (AESysWindowExists()) {
    gameManager->Run();
  }

  gameManager->Uninitialize();
  AESysExit();

  return 0;
}
