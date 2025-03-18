#include "PlayerController.hpp"
#include <Controller/CameraController.hpp>
#include "Controller/InputComponent.hpp"
#include "Core.hpp"
#include "Objects/Character.hpp"
#include "Objects/Object.hpp"
#include "Player.hpp"


#include "Objects/Manager/GameplayManager.hpp"

namespace game {

void PlayerController::Update()
{
  m_inputSystem.UpdateInput(m_controllerId);
  std::string action = m_inputSystem.GetAction();

  if (m_character->GetIsIdle())
    m_character->Move(m_inputSystem.GetMovement());

  // Action callback
  if      (action == "roll" && m_character->GetIsIdle())  m_character->Dash();
  else if (action == "basic") {
    if (!m_character->GetIsIdle())
      m_character->WantsToAttackAgainBasic(m_inputSystem.GetLastMovement().x);

    m_character->BasicAttack();
  }
  else if (action == "super")
    m_character->SuperAttack();

  /*if (!m_character->GetAlive()) {
    if (m_controllerId != -1) {
      if (AEInputGamepadButtonPressed(m_controllerId, AE_GAMEPAD_START)) {
        GameplayManager::GetInstance()->RespawnPlayer(dynamic_cast<Player*>(m_character));
      }
    }
  }*/

  // #ifdef _DEBUG
  // std::cout << m_character->transform.position.x << ", " << m_character->transform.position.y <<
  //           ", " << m_character->transform.position.z << std::endl;
  // std::cout << m_state << ", " << m_controllerId << std::endl;
  // #endif
  

  // Sprite flip
  if (m_character->GetIsIdle()) {
    if (m_inputSystem.GetLastMovement().x > 0)
      m_character->transform.relativeScale.x = 1;
    else
      m_character->transform.relativeScale.x = -1;
  }

}

void PlayerController::PlayerDamagedFeedback() {

  // feedback
  if(m_controllerId == -1)
    return;

  m_inputSystem.DoGamepadRumble(m_controllerId, 1, .15f);

  // TODO: dante the fucking shake camera its not exposed >:( -d
 
}

void PlayerController::PlayerAttackFeedback(){
  if(m_controllerId == -1)
    return;

  m_inputSystem.DoGamepadRumble(m_controllerId, .75f, .05f);
}



} // namespace game
