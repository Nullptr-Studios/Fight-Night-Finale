#include "Enemy.hpp"
#include "DamageSystem/DamageEvent.hpp"
#include "Factory.hpp"
#include "Player/Player.hpp"
#include "core.hpp"
#include "glm/geometric.hpp"

namespace game {
void Enemy::Serialize() {
  Character::Serialize();
  m_distanceToAttack = j["distanceToAttack"];
}

void Enemy::Init() {
  Character::Init();

  transform.relativeScale = glm::vec2(1);

  // Setup Animation
  auto anim = GET_ANIMATION->LoadTextureAtlas("assets/ProtoPlayer.json");
  m_animComp->SetTextureAtlas(anim);
  m_animComp->SetCurrentAnim("Idle");
  SetTexture(anim->textureStr.c_str());
  m_animComp->PlayAnim();

  // setup player collider
  m_collider->box.Set(25, 25, 50, 50, 25, transform.offset);
  m_collider->SetColliderType(Sigma::Collision::COLLISION);
  m_collider->damage = 1.0f;
  m_collider->SetOwner(this);

  
}

void Enemy::Start() {
  Character::Start();
  m_state = FOLLOW;
  m_player = GET_FACTORY->FindObject<Player>("Player");
  m_debugCol = GET_FACTORY->CreateObject<Sigma::Actor>("Debug Attack");
}

bool Enemy::OnCollision(Sigma::Collision::CollisionEvent& e) {
  Character::OnCollision(e);
  return false;
}

void Enemy::OnDamage(const Sigma::Damage::DamageEvent& e) {
  Character::OnDamage(e);

  if (!GetAlive()) m_state = DEAD;
}

void Enemy::Update(double delta) {
  Character::Update(delta);
  m_distance = m_player->transform.GetDepthPosition() - transform.position;

  m_collider->DebugDraw(m_debugCol, this, "assets/core/debug_blue.png");

  switch (m_state) {
    default: m_state = FOLLOW;
    case FOLLOW: OnFollow(); break;
    // case SEPARATE: OnSeparate(); break;
    case ATTACK: OnAttack(); break;
    case DEAD: OnDead(); break;
  }
}

void Enemy::OnFollow() {
  auto direction = glm::normalize(m_distance);
  // We use the .z instead of the .y to ignore if the player is jumping -x
  Move( {direction.x, direction.y} );

  if (glm::length(m_distance) < m_distanceToAttack) {
    if (m_distance.y >= 5.0f){
      Move( {0.0f, direction.y});
    } else {
      m_state = ATTACK;
    }
  };

  // Swaps the sprite if not facing the same way -x
  if ((direction.x >= 0) != (transform.relativeScale.x >= 0)) {
    transform.relativeScale.x *= -1;
  }
}

void Enemy::OnSeparate() {
  auto direction = glm::normalize(m_distance) * -1.0f;
  // We use the .z instead of the .y to ignore if the player is jumping -x
  Move( {direction.x, direction.y} );

  if (glm::length(m_distance) > m_distanceToAttack) m_state = FOLLOW;

  // Swaps the sprite if not facing the same way -x
  if ((direction.x >= 0) != (transform.relativeScale.x >= 0)) {
    transform.relativeScale.x *= -1;
  }
}

void Enemy::OnAttack() {
  BasicAttack();

  if (glm::length(m_distance) > m_distanceToAttack) m_state = FOLLOW;
  // Ignore separate logic for now
  // if (glm::length(m_distance) < m_distanceToAttack - 15.0f) m_state = SEPARATE;
}

void Enemy::OnDead() { }

void Enemy::Destroy() { Character::Destroy(); }

}
