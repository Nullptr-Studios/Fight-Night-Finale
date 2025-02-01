#include "PlayerController.hpp"
#include "Controller/InputSystem.hpp"
#include "Objects/Character.hpp"
#include "Objects/Object.hpp"

namespace game {

void PlayerController::Update() {
  m_inputSystem.UpdateInput(m_controllerId);
  if (m_state == ACTION) return;
    std::string action = m_inputSystem.GetAction();
    //Sets air state if jumping
  if (action == "jump") {
      m_state = AIR;
  }
  //Plays action if in an action
  if (!action.empty()) {
    PlayAction(action);
    return;
  }
  //Movement
  switch (m_state) {
    case AIR:
      UpdateJump();
      break;
    default:
      UpdateMovement();
      break;
  }
  #ifdef _DEBUG
  std::cout << m_character->transform.position.x << ", " << m_character->transform.position.y <<
            ", " << m_character->transform.position.z << std::endl;
  std::cout << m_state << ", " << m_controllerId << std::endl;
  #endif
}


void PlayerController::UpdateMovement() {
  glm::vec2 movement = m_inputSystem.GetMovement();

  // Check for movement input
  if (movement.x!=0.f || movement.y!=0.f) {
    m_facingDirection = glm::vec2(movement.x, movement.y);
  }

  // X-Movement
  UpdateCoordinate(movement.x, m_velocity.x, m_acceleration, m_maxVelocity);

  // Y-Movement
  UpdateCoordinate(movement.y, m_velocity.y, m_acceleration, m_maxVelocity);

  // Update position based on movement direction and velocity
  m_position = {static_cast<float>(m_velocity.x * AEGetFrameTime()),
                  static_cast<float>(m_velocity.y * AEGetFrameTime()),
                  static_cast<float>(m_velocity.y * AEGetFrameTime())};
  m_character->transform.position += m_position;

  // Transition to MOVING state if velocity is above a small threshold
  if (std::fabs(m_velocity.x) > 0.1f || std::fabs(m_velocity.y) > 0.1f) {
    m_state = MOVING;
  }
  else if (m_velocity.x <=  0.f && m_velocity.y <= 0.f) {
      m_state = IDLE; // Transition to IDLE when velocity is 0
  }
  // TODO: Movement Animations

}

void PlayerController::UpdateJump() {
  glm::vec2 movement = m_inputSystem.GetMovement();

  if (m_state != AIR) return;
    // X-Movement
    UpdateCoordinate(movement.x, m_velocity.x, m_airAccel.x, m_airMaxVelocity.x);

    // Jump Logic: Y Movement
    if (m_jumpPeaked) {
      if (m_character->transform.position.y > m_character->transform.position.z) {
        // Apply deceleration until Y <= Z
        m_velocity.y = std::clamp(m_velocity.y - m_airAccel.y, -m_airMaxVelocity.y, 0.0f);
      } else {
        // Exit out of jump movement when Y <= Z
        m_character->transform.position.y = m_character->transform.position.z;
        m_jumpPeaked = false;
        m_velocity.y = 0.f;
        m_velocity.z = 0.f;
        m_state = IDLE;
        return;
      }
    } else {
      // Check if Jump height has been reached
      if (m_character->transform.position.y - m_character->transform.position.z >= m_jumpHeight ) {
        m_jumpPeaked = true;
      } else {
        // Apply vertical acceleration until Jump height is reached
        m_velocity.y = std::clamp(m_velocity.y + m_airAccel.y, 0.0f, m_airMaxVelocity.y);
      }
    }
    //Update movement
    m_position = {static_cast<float>(m_velocity.x * AEGetFrameTime()),
    static_cast<float>(m_velocity.y * AEGetFrameTime()),
    0.0f};
    m_character->transform.position += m_position;
    // TODO: jump animations

}

void PlayerController::UpdateCoordinate (const float & coordinate, float& velocity,
                                        const float & acceleration, const float& maxVelocity) {
   if (coordinate!=0.f) {
     // Apply acceleration and clamp velocity
     velocity = std::clamp(velocity + acceleration * coordinate , -maxVelocity, maxVelocity);
   } else {
      // Deceleration: When there's no movement, decrease velocity
      if (velocity != 0.f) {
        if (velocity > 0.01f) {
          velocity -= acceleration;
          velocity = std::min(velocity, 0.0f);
        } else if (velocity < -0.01f) {
          velocity += acceleration;
          velocity = std::max(velocity, 0.0f);
        }
      }
    }
}

void PlayerController::PlayAction(const std::string &action) {
  if (m_state == AIR) {
    m_state = ACTION;
    // TODO: Do AIR combat animations
    // After animation, return to AIR
    m_state = AIR;
  } else {
    m_state = ACTION;
    std::cout << "Action: " << action << "\n";
    // TODO: Do combat animations
    // After animation return to IDLE

    m_velocity.x = 0.0f;
    m_velocity.y = 0.0f;
    EndAction(action);
  }
}

void PlayerController::EndAction(const std::string &action) { m_state = IDLE; }

} // namespace game