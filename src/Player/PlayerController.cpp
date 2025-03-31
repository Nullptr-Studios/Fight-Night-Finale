#include "PlayerController.hpp"
#include <Controller/CameraController.hpp>
#include "Controller/InputComponent.hpp"

#include "Objects/Character.hpp"
#include "Objects/Object.hpp"



namespace game {

PlayerController::~PlayerController(){
  if(m_controllerId != -1)
    m_inputSystem.StopGamepadRumble(m_controllerId);
};

void PlayerController::Update()
{
  m_inputSystem.UpdateInput(m_controllerId);
  std::string action = m_inputSystem.GetAction();

  m_character->Move(m_inputSystem.GetMovement());

  // Action callback
  if      (action == "roll")  m_character->Dash();
  else if (action == "basic") {
    if (!m_character->GetIsIdle())
      m_character->WantsToAttackAgainBasic(m_inputSystem.GetLastMovement().x);
    
    m_character->BasicAttack();
  }
  else if (action == "super")
    m_character->SuperAttack();

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

  m_inputSystem.DoGamepadRumble(m_controllerId, 1, .25f);

  // TODO: dante the fucking shake camera its not exposed >:( -d
 
}

void PlayerController::PlayerAttackFeedback(){
  if(m_controllerId == -1)
    return;

  m_inputSystem.DoGamepadRumble(m_controllerId, .75f, .1f);
}


} // namespace game
