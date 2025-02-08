#include "Enemy.hpp"
#include "Player/Player.hpp"
#include "core.hpp"
#include "glm/geometric.hpp"

namespace game {

void Enemy::Serialize() {
  Character::Serialize();
  m_distanceToAttack = j["distanceToAttack"];
}

void Enemy::Start() {
  m_state = FOLLOW;
  m_player = GET_FACTORY->FindObject("Player");
}

bool Enemy::OnCollision(Sigma::Collision::CollisionEvent& e) {
  Character::OnCollision(e);
  return false;
}

void Enemy::Update(double delta) {
  switch (m_state) {
    default: m_state = FOLLOW;
    case FOLLOW: OnFollow(delta); break;
    case ATTACK: OnAttack(delta); break;
    case DEAD: OnDead(delta); break;
  }
}

void Enemy::OnFollow(double delta) {
  glm::vec3 targetPosition = m_player->transform.position - transform.position;
  targetPosition.y = targetPosition.z; // Removes player jump -x

  if (glm::length(targetPosition) < m_distanceToAttack) m_state = ATTACK;

  targetPosition = glm::normalize(targetPosition);
  Move( {targetPosition.x, targetPosition.y} );
}

void Enemy::OnAttack(double delta) {
  BasicAttack();
}

void Enemy::OnDead(double delta) { }

}

