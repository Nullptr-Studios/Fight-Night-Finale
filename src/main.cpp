/**
 * @file main.cpp
 * @author Xein
 * @date 1/29/2025
 */

#include <aecore/AEEngine.h>
#include "GameManager.hpp"

int main() {
  std::unique_ptr<FNFE::GameManager> gameManager = std::make_unique<FNFE::GameManager>("Game", 800, 600);

  while (AESysWindowExists()) {
    gameManager->Run();
  }

  gameManager->Uninitialize();
  AESysExit();

  return 0;
}
