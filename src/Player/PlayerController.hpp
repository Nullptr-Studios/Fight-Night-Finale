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
 * @enum  PlayerState 
 * @brief Stores the current state the player is in
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
  [[nodiscard]] glm::vec2 GetFacingDirection() const { return m_facingDirection; }
  [[nodiscard]] float GetMaxVelocity() const { return m_maxVelocity; }
  void SetMaxVelocity(float velocity) { m_maxVelocity = velocity; }
  void GetControllerID() {m_inputSystem.CheckControllers();}

private:
  float m_acceleration = 25.0f; ///< @brief player acceleration
  glm::vec2 m_airAccel = {25.0f, 50.0f}; ///< @brief player air acceleration

  float m_jumpHeight = 150.0f; ///< @brief player max jump height
  float m_maxVelocity = 400.0f; ///< @brief player max velocity
  glm::vec2 m_airMaxVelocity = glm::vec2(400.0f); ///> @brief player max air velocity
  glm::vec3 m_velocity = glm::vec3(0.f); ///>@brief player velocity

  // TODO: Possibly deprecate the bool in favor of a parabolic function for the jump
  bool m_jumpPeaked = false; ///< @brief Checks if Y-Coordinate has reached jumpHeight

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
  static static void UpdateCoordinate(const float& coordinate, float& velocity, const float& acceleration, const float& maxVelocity);
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