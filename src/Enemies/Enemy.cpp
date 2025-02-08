#include "Enemy.hpp"
#include "Factory.hpp"
#include "Player/Player.hpp"
#include "core.hpp"
#include "glm/geometric.hpp"

namespace game {
void Enemy::Serialize() {
  Character::Serialize();
  m_distanceToAttack = j["distanceToAttack"];
}

void Enemy::Init() { Character::Init(); }

void Enemy::Start() {
  Character::Start();
  m_state = FOLLOW;
  m_player = GET_FACTORY->FindObject<Player>("Player");
}

bool Enemy::OnCollision(Sigma::Collision::CollisionEvent& e) {
  Character::OnCollision(e);
  return false;
}

void Enemy::Update(double delta) {
  Character::Update(delta);
  m_distance = m_player->transform.GetDepthPosition() - transform.position;

  switch (m_state) {
    default: m_state = FOLLOW;
    case FOLLOW: OnFollow(delta); break;
    case ATTACK: OnAttack(delta); break;
    case DEAD: OnDead(delta); break;
  }
}

void Enemy::OnFollow(double delta) {
  auto direction = glm::normalize(m_distance);
  // We use the .z instead of the .y to ignore if the player is jumping -x
  Move( {direction.x, direction.y} );

  if (glm::length(m_distance) < m_distanceToAttack) m_state = ATTACK;
}

void Enemy::OnAttack(double delta) {
  BasicAttack();

  if (glm::length(m_distance) > m_distanceToAttack) m_state = FOLLOW;
}

void Enemy::OnDead(double delta) { }

void Enemy::Destroy() { Character::Destroy(); }

}
