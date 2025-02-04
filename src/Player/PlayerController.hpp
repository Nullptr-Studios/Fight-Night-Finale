/**
 * @file PlayerController.hpp
 * @author alexey
 * @date 1/22/2025
 *
 * @brief Manages and interprets input to action
 */
#pragma once
#include "Controller/ControllerComponent.hpp"
#include "Controller/InputSystem.hpp"

namespace game {
class InputSystem;

/**
 * @class PlayerController
 * @brief Manages per player input and actions
 */
class PlayerController : public FNFE::ControllerComponent {
public:
  explicit PlayerController(FNFE::Character *character) :
      ControllerComponent(character), m_inputSystem("assets/core/keybinds.json") {}
  ~PlayerController() override = default;
  void Update() override; ///< @brief Call this every frame to update the player position

  void GetControllerID() {m_controllerId = m_inputSystem.CheckControllers();}

private:
  /**
   * @brief helper function to update movement
   */
  void UpdateMovement();
  /**
   * @brief helper function to update jump movement
   *
   */
  void UpdateJump();
  /**
   * @brief handles movement for a coordinate
   * @param coordinate vec2 movement.coordinate
   * @param velocity vec3.coordinate velocity for player movement
   * @param acceleration acceleration
   * @param maxVelocity maximum velocity
   */
  void UpdateCoordinate(const float& coordinate, float& velocity, const float& acceleration, const float& maxVelocity);
  // TODO: have a combo buffer to keep track of current combo
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
  FNFE::InputSystem m_inputSystem; ///< @brief Input System that manages input

};

} // namespace FNFE