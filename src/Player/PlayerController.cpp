#include "PlayerController.hpp"
#include "Controller/InputSystem.hpp"
#include "Objects/Character.hpp"
#include "Objects/Object.hpp"

namespace game {

void PlayerController::CheckControllers() {
  for (int i = 0; i<=3; i++) {
    if (AEInputGamepadConnected(i)) {
      m_controllerId = i;
      return;
    }
  }
  m_controllerId = -1;
}

void PlayerController::Update() {
  CheckControllers();
  m_inputSystem.UpdateInput(m_controllerId);
  if (m_state != ACTION) {
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
    std::cout << m_state << std::endl;
    #endif
  }
}

void PlayerController::UpdateMovement() {
  glm::vec2 movement = m_inputSystem.GetMovement();

  // Check for movement input
  bool isMovingX = movement.x != 0.f;
  bool isMovingY = movement.y != 0.f;
  if (isMovingX || isMovingY) {
    m_facingDirection = glm::vec2(movement.x, movement.y);
  }

    if (isMovingX) {
      // Apply acceleration and clamp velocity
      velocityX = std::clamp(velocityX + acceleration * movement.x , -maxVelocity, maxVelocity);
    } else {
      // Deceleration: When there's no movement, decrease velocity
      if (velocityX != 0.f) {
        if (velocityX > 0.f) {
          velocityX -= acceleration;
          if (velocityX < 0.f) velocityX = 0.f;  // Clamp to zero if overshooting
        } else if (velocityX < 0.f) {
          velocityX += acceleration;
          if (velocityX > 0.f) velocityX = 0.f;  // Clamp to zero if overshooting
        }
      }
    }

    if (isMovingY) {
      velocityY = std::clamp(velocityY + acceleration * movement.y, -maxVelocity, maxVelocity);
    } else {
      // Deceleration: When there's no movement, decrease velocity
      if (velocityY != 0.f) {
        if (velocityY > 0.f) {
          velocityY -= acceleration;
          if (velocityY < 0.f) velocityY = 0.f;  // Clamp to zero if overshooting
        } else if (velocityY < 0.f) {
          velocityY += acceleration;
          if (velocityY > 0.f) velocityY = 0.f;  // Clamp to zero if overshooting
        }
      }
    }

    // Update position based on movement direction and velocity
    m_position = {static_cast<float>(velocityX * AEGetFrameTime()),
      static_cast<float>(velocityY * AEGetFrameTime()),
      static_cast<float>(velocityY * AEGetFrameTime())};
    m_character->transform.position += m_position;

    // Transition to MOVING state if velocity is above a small threshold
    if (std::abs(velocityX) > 0.1f || std::abs(velocityY) > 0.1f) {
      m_state = MOVING;

      //TODO: ADD WALKING ANIMATIONS

      if (velocityX > 0.f || velocityY > 0.f) {}
    } else {
      m_state = IDLE; // Transition to IDLE when velocity is 0
    }
  }

void PlayerController::UpdateJump() {
  glm::vec2 movement = m_inputSystem.GetMovement();

  // Check for movement input
  bool isMovingX = movement.x != 0.f;
  bool isMovingY = movement.y != 0.f;
  if (isMovingX || isMovingY) {
    m_facingDirection = glm::vec2(movement.x, movement.y);
  }

  if (m_state == AIR) {
    // X-Movement
    if (isMovingX) {
      // Apply acceleration and clamp velocity
      velocityX = std::clamp(velocityX + inAirAccelerationX * movement.x , -maxAirVelocityX, maxAirVelocityX);
    } else {
      // Deceleration: When there's no movement, decrease velocity
      if (velocityX != 0.f) {
        if (velocityX > 0.f) {
          velocityX -= inAirAccelerationX;
          if (velocityX < 0.f) velocityX = 0.f;  // Clamp to zero if overshooting
        } else if (velocityX < 0.f) {
          velocityX += inAirAccelerationX;
          if (velocityX > 0.f) velocityX = 0.f;  // Clamp to zero if overshooting
        }
      }
    }

    // Jump Logic: Y Movement
    if (jumpPeaked) {
      if (m_character->transform.position.y > m_character->transform.position.z) {
        // Apply deacceleration until Y <= Z
        velocityY = std::clamp(velocityY - inAirAccelerationY, -maxAirVelocityY, 0.0f);
      } else {
        // Exit out of jump movement when Y <= Z
        m_character->transform.position.y = m_character->transform.position.z;
        jumpPeaked = false;
        velocityY = 0.f;
        velocityZ = 0.f;
        m_state = IDLE;
        return;
      }
    } else {
      // Check if Jump height has been reached
      if (m_character->transform.position.y - m_character->transform.position.z >= jumpHeight ) {
        jumpPeaked = true;
      } else {
        // Apply vertical acceleration until Jump height is reached
        velocityY = std::clamp(velocityY + inAirAccelerationY, 0.0f, maxAirVelocityY);
      }
    }
    //Update movement
    m_position = {static_cast<float>(velocityX * AEGetFrameTime()),
    static_cast<float>(velocityY * AEGetFrameTime()),
    0.0f};
    m_character->transform.position += m_position;

    //TODO: Maybe add jumping animations?

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

    velocityX = 0.0f;
    velocityY = 0.0f;
    EndAction(action);
  }
}

void PlayerController::EndAction(const std::string &action) { m_state = IDLE; }

} // namespace FNFE