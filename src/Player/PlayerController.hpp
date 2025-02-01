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
 * @enum PlayerState for the current state the player is in
 */
enum PlayerState {
  IDLE, ///< @brief The player is standing still
  MOVING, ///< @brief The player is moving
  AIR, ///< @brief The player is in the air
  ACTION, ///< @brief The player is preforming an action
};

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
  /**
   * @brief Get the direction the player is facing
   * This is like the direction the player is moving, but it never returns a zero value
   * @return The direction the player last moved
   */
  glm::vec2 GetFacingDirection() const { return m_facingDirection; }

  float GetMaxVelocity() const { return maxVelocity; }
  void SetMaxVelocity(float velocity) { maxVelocity = velocity; }

private:
  float acceleration = 25.0f; ///< @brief player acceleration
  float inAirAccelerationX = 25.0f; ///< @brief player X acceleration while in AIR
  float inAirAccelerationY = 50.0f; ///<  @brief player Y acceleration while in AIR

  float jumpHeight = 150.0f; ///< @brief maximum jump height
  float maxVelocity = 400.0f; ///< @brief maximum velocity
  float maxAirVelocityX = 400.0f; ///< @brief max X velocity in AIR
  float maxAirVelocityY = 400.0f; ///< @brief max Y velocity in AIR

  //TODO: Possibly deprecate the bool in favor of a parabolic function for the jump
  bool jumpPeaked = false; ///< @brief Checks if Y-Coorinate has reached jumpHeight

  float velocityX = 0; ///< @brief player velocity variable, 0 by default
  float velocityY = 0; ///< @brief player velocity variable, 0 by default
  float velocityZ = 0; ///< @brief player velocity variable, 0 by default

  /**
   * @brief checks if any gamepad is connected, sets controller id to gamepad id
   */
  // TODO: make this work with multiple controllers
  void CheckControllers();
  /**
   * @brief helper function to update movement
   */
  void UpdateMovement();
  /**
   * @brief helper function to update jump movement
   *
   */
  void UpdateJump();
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

  int m_controllerId = -1; ///< @brief ID of the controller being used
  FNFE::InputSystem m_inputSystem; ///< @brief Input System that manages input
  PlayerState m_state = IDLE; ///< @brief Stores current player state

  glm::vec2 m_facingDirection = glm::vec2(1.0f, 0.0f); ///< @brief Direction the player last moved
};

} // namespace FNFE