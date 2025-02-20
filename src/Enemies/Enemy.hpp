/**
 * @file Enemy.hpp
 * @author Xein
 * @date 20/02/25
 *
 * @brief Contains definition of the base enemy class
 */
#pragma once
#include "Objects/Character.hpp"

namespace game {

class Enemy : public Sigma::Character {
protected:
  Enemy(const Sigma::id_t id, std::string& jsonPath) : Character(id, jsonPath) {}

public:
  void Init() override;
  void Start() override;
  void Update(double delta) override;

  #pragma region State IDs

  // This are helpfer functions in order to not have to remember the IDs
  // They are done with constexpr instead of an enum so that classes that inherit can simply add
  // their own for their custom state logic
  // Constexpr are resolved on compile time so you don't have to worry about space in memory -x
  static constexpr char STATE_IDLE = 0;       ///< @constexpr STATE_IDLE        The enemy does nothing
  static constexpr char STATE_FOLLOW = 1;     ///< @constexpr STATE_FOLLOW      The enemy follows the player
  static constexpr char STATE_WAIT = 2;       ///< @constexpr STATE_WAIT        The enemy waits for a set amount of time
  static constexpr char STATE_DISPERSE = 3;   ///< @constexpr STATE_DISOERSE    The enemy moves away from the player
  static constexpr char STATE_AVOID = 4;      ///< @constexpr STATE_AVOID       The enemy moves away from other enemies
  static constexpr char STATE_REPOSITION = 5; ///< @constexpr STATE_REPOSITION  The enemy repositions after a combo
  static constexpr char STATE_ATTACK = 6;     ///< @constexpr STATE_ATTACK      The enemy attacks the player

  #pragma endregion

  /**
   * @brief Changes the current state variable
   * State change will happen on the next frame
   * @param state State to change to
   */
  void SetState(char state);

  /**
   * @brief Binds a function to the state list
   * EVERY function must be binded before being accessed on the child, as behaviour changes are expected on all different enemies.
   * You can just use @c std::bind() for binding a function
   *
   * @param state ID of the state to bind
   * @param function Function to bind to the state
   */ 
  void BindState(char state, const std::function<void()>& function);

  /**
   * @brief Sets the timer variables and changes state
   * @warn The timer state is an special state and should only be called through this function
   * @param time Amount of time to spend on the timer
   * @param nextState Next state to change once the timer finishes
   */
  void WaitSeconds(float time, char nextState);

private:
  std::map<char, std::function<void()>> m_states = {};
  char m_currentState = 0;

  // Placeholder idle state
  void IdleState() { }

  // Timer methods
  void TimerState();
  float m_timer = 0.0f;
  float m_timerSeconds = -1.0f;
  char m_timerNextState = STATE_IDLE;
};

}
