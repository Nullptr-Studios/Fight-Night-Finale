#include "PlayerController.hpp"
#include "Controller/InputSystem.hpp"
#include "Objects/Character.hpp"
#include "Objects/Object.hpp"

namespace game {

void PlayerController::Update()
{
  m_inputSystem.UpdateInput(m_controllerId);
  std::string action = m_inputSystem.GetAction();
  

  m_character->Move(m_inputSystem.GetMovement());
  if (action == "jump") {
    m_character->Jump();
  }

  // Sprite flip
  if (m_inputSystem.GetLastMovement().x > 0) {
    m_character->transform.relativeScale.x = 2;
  }
  else
  {
    m_character->transform.relativeScale.x = -2;
  }

}


void PlayerController::PlayAction(const std::string &action) {
 
    EndAction(action);
}

void PlayerController::EndAction(const std::string &action) {  }

} // namespace game