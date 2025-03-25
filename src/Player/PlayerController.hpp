/**
 * @file PlayerController.hpp
 * @author alexey
 * @date 1/22/2025
 *
 * @brief Manages and interprets input to action
 */

#pragma once
#include "Controller/ControllerComponent.hpp"
#include "Controller/InputComponent.hpp"

namespace game {
class InputSystem;

/**
 * @class PlayerController
 * @brief Manages per player input, actions and feedback
 */
class PlayerController : public Sigma::ControllerComponent {
public:
  explicit PlayerController(Sigma::Character *character) :
      ControllerComponent(character), m_inputSystem("assets/core/keybinds.json") {}

  ~PlayerController() override;
   
  void Update() override;

  /**
   * @beief Player Movement Feedback logic
   */
  void PlayerDamagedFeedback();
  
  /**
   * @brief Player Attack Feedback logic
   */
  void PlayerAttackFeedback();

  /**
   * @brief Set the Controller ID
   * @param id the ID to set
   */
  void SetControllerID(int id) {m_controllerId = id;}

private:

  int m_controllerId{}; ///< @brief ID of the controller being used
  Sigma::InputComponent m_inputSystem; ///< @brief Input System that manages input

};

} // namespace Sigma
