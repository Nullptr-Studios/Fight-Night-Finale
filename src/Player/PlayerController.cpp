#include "PlayerController.hpp"
#include "Controller/InputSystem.hpp"
#include "Objects/Character.hpp"
#include "Objects/Object.hpp"

namespace game {

void PlayerController::Update() {
  m_inputSystem.UpdateInput(m_controllerId);
    std::string action = m_inputSystem.GetAction();
    //Sets air state if jumping
  m_character->Move(m_inputSystem.GetMovement());

  // Action callback
  if      (action == "roll")  m_character->Jump();
  else if (action == "basic") m_character->BasicAttack();
  else if (action == "super") m_character->SuperAttack();

  // #ifdef _DEBUG
  // std::cout << m_character->transform.position.x << ", " << m_character->transform.position.y <<
  //           ", " << m_character->transform.position.z << std::endl;
  // std::cout << m_state << ", " << m_controllerId << std::endl;
  // #endif
}

} // namespace game
