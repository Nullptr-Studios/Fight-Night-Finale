/**
 * @file main.cpp
 * @author Xein
 * @date 1/29/2025
 */

#include <aecore/AEEngine.h>
#include "GameManager.hpp"
#include "PrototypeScene.hpp"

int main() {
  std::unique_ptr<Sigma::GameManager> gameManager = std::make_unique<Sigma::GameManager>("Game", 800, 600);
  auto scene = new game::PrototypeScene("Main", 0, "assets/prototype-scene-2/ProtoScene2.json");
  gameManager->LoadScene(scene);

  while (AESysWindowExists()) {
    gameManager->Run();
  }

  gameManager->Uninitialize();
  AESysExit();

  return 0;
}
