#include "DefaultEnemy.hpp"
#include <random>
#include "Polygon.hpp"

#include "Factory.hpp"

namespace game {

void DefaultEnemy::Start() {
  Enemy::Start();

  BindState(STATE_FOLLOW, std::bind(&DefaultEnemy::FollowState, this));
  BindState(STATE_DISPERSE, std::bind(&DefaultEnemy::DisperseState, this));
  BindState(STATE_AVOID, std::bind(&DefaultEnemy::AvoidState, this));
  BindState(STATE_REPOSITION, std::bind(&DefaultEnemy::RepositionState, this));
  BindState(STATE_ATTACK, std::bind(&DefaultEnemy::AttackState, this));
  BindState(STATE_DEAD, std::bind(&DefaultEnemy::DeadState, this));
}

void DefaultEnemy::FollowState() {
  if (!m_isIdle) return;

  auto direction = glm::normalize(m_distance);
  // We use the .z instead of the .y to ignore if the player is jumping -x
  Move( {direction.x, direction.y} );

  if (fabs(m_distance.x) < m_attackDistance) {
    if (fabs(m_distance.y) > 5.0f){
      Move( {0.0f, direction.y});
    } else {
      SetState(STATE_ATTACK);
    }
  };

  // Swaps the sprite if not facing the same way -x
  if ((direction.x >= 0) != (transform.relativeScale.x >= 0)) {
    transform.relativeScale.x *= -1;
  }
}

void DefaultEnemy::DisperseState() {
  if (!m_isIdle) return;
  glm::vec2 position = {transform.GetDepthPosition().x, transform.GetDepthPosition().y};

  // Calculates the point the enemy will go back to -x
  if (m_randomPosition.x == 0 && m_randomPosition.y == 0) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> distrib_x( 0, 30);
    std::uniform_int_distribution<> distrib_y(-15,  15);

    m_randomPosition.x = (m_player->transform.GetDepthPosition().x);
    if (m_randomPosition.x - position.x >= 0) m_randomPosition.x -= m_attackDistance + static_cast<float>(distrib_x(gen));
    else m_randomPosition.x += m_attackDistance - static_cast<float>(distrib_x(gen));
    m_randomPosition.y = (m_player->transform.GetDepthPosition().y + static_cast<float>(distrib_y(gen)));

    // Recalculate if point is out of bounds -x
    if (!m_sceneBoundsPoly->IsPointInside(m_randomPosition)) {
      m_randomPosition = {0.0f, 0.0f};
      SetState(STATE_FOLLOW);
    }
  }

  Move(glm::normalize(m_randomPosition - position));
  if (glm::distance(position, m_randomPosition) < 1.0f) {
    m_randomPosition = {0.0f, 0.0f};
    SetState(STATE_FOLLOW);
  }

  // TODO: THIS IS BROKEN
  // Swaps the sprite if not facing the same way -x
  // if ((direction.x <= 0) != (transform.relativeScale.x <= 0)) {
  //   transform.relativeScale.x *= -1;
  // }
}

void DefaultEnemy::AvoidState() {
  // TODO: Implement this
}

void DefaultEnemy::RepositionState() {
  if (!m_isIdle) return;
  glm::vec2 position = {transform.GetDepthPosition().x, transform.GetDepthPosition().y};

  if (m_randomPosition.x == 0.0f && m_randomPosition.y == 0.0f) {
    auto playerScale = m_player->transform.scale;
    auto playerPosition = m_player->transform.position;

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> distrib_x(-playerScale.x * 2, playerScale.x * 2);
    std::uniform_int_distribution<> distrib_y(-playerScale.y, playerScale.y);

    m_randomPosition = { playerPosition.x + distrib_x(gen), playerPosition.y + distrib_y(gen) };

    // Avoid SEPARATE state if point is out of bounds -x
    if (!m_sceneBoundsPoly->IsPointInside(m_randomPosition)) {
      m_randomPosition = {0.0f, 0.0f};
      RepositionState();
      return;
    }
  }

  Move(glm::normalize(m_randomPosition - position));
  if (glm::distance(position, m_randomPosition) < 1.0f) {
    m_randomPosition = {0.0f, 0.0f};
    WaitSeconds(0.5f, STATE_FOLLOW);
  }

  // Swaps the sprite if not facing the same way -x
  if ((glm::normalize(m_randomPosition - position).x >= 0) != (transform.relativeScale.x >= 0)) {
    transform.relativeScale.x *= -1;
  }
}

void DefaultEnemy::AttackState() {
  if (m_isIdle) {
    if (fabs(m_distance.x) < (m_attackDistance - 20.0f)) {
      SetState(STATE_DISPERSE);
    }
    if (fabs(m_distance.x) > m_attackDistance || fabs(m_distance.y) > 5.0f) {
      SetState(STATE_FOLLOW);
    }
  }

  BasicAttack();
}

void DefaultEnemy::DeadState() {
  // GET_FACTORY->DestroyObject(m_debugCol->GetId());
  GET_FACTORY->DestroyObject(GetId());
}

}
