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
 * @brief Manages per player input and actions
 */
class PlayerController : public Sigma::ControllerComponent {
public:
  explicit PlayerController(Sigma::Character *character) :
      ControllerComponent(character), m_inputSystem("assets/core/keybinds.json") {}
  ~PlayerController() override = default;
  void Update() override;

  //void GetControllerID() {m_controllerId = m_inputSystem.CheckControllers();}

  /**
   * @brief Set the Controller ID
   * @param id the ID to set
   */
  void SetControllerID(int id) {m_controllerId = id;}

private:

  /**
   * @brief plays specifed action
   * @param action specifed action
   */
  void PlayAction(const std::string &action);
  /**
   * @brief function played when action is ended
   * @param action the action that ended
   */
  void EndAction(const std::string &action);

  int m_controllerId; ///< @brief ID of the controller being used
  Sigma::InputComponent m_inputSystem; ///< @brief Input System that manages input

};

} // namespace Sigma