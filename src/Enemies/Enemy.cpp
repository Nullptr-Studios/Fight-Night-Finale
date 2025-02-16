#include "Enemy.hpp"
#include <random>
#include "DamageSystem/DamageEvent.hpp"
#include "Factory.hpp"
#include "GameManager.hpp"
#include "Player/Player.hpp"
#include "Polygon.hpp"
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
  auto anim = GET_ANIMATION->LoadTextureAtlas("assets/EnemyPrototype.json");
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

void Enemy::OnFullComboPerformed() { m_state = RANDOM_SPARCE; }

void Enemy::Enable(std::array<Player *, 2> players) {
  if (!players[0]) {
    if (!players[1]) {
      std::cout << "[Enemy] No players sent to \"" << GetName() << "\"\n";
      std::cout << "[Enemy] Aborting initialization\n";
      return;
    }

    // This is a weird case in which the player 2 exist but not the player 1 -x
    // Maybe player1 died???? -x
    m_player = players[1];
  } else if (!players[1]) {
    m_player = players[0];
  } else {
    float distancePlayer1 = glm::distance(players[0]->transform.position, transform.position);
    float distancePlayer2 = glm::distance(players[1]->transform.position, transform.position);

    if (distancePlayer1 < distancePlayer2) {
      m_player = players[0];
    } else {
      m_player = players[1];
    }
  }

  m_state = FOLLOW;
}

void Enemy::Update(double delta) {
  Character::Update(delta);
  m_distance = m_player->transform.GetDepthPosition() - transform.GetDepthPosition();

  m_collider->DebugDraw(m_debugCol, this, "assets/core/debug_blue.png");

  switch (m_state) {
    case IDLE: break;
    case WAIT: OnWait(delta); break;
    default: m_state = FOLLOW;
    case FOLLOW: OnFollow(); break;
    case SEPARATE: OnSeparate(); break;
    case RANDOM_SPARCE: OnRandomSparce(); break;
    case ATTACK: OnAttack(); break;
    case DEAD: OnDead(); break;
  }
}

void Enemy::OnWait(double delta) {
  m_timer += static_cast<float>(delta);

  if (m_timer >= m_timerSeconds) {
    m_state = m_timerNextState;

    m_timerNextState = FOLLOW;
    m_timerSeconds = 0.0f;
    m_timer = 0.0f;
  }
}

void Enemy::OnFollow() {
  if (!m_isIdle) return;

  auto direction = glm::normalize(m_distance);
  // We use the .z instead of the .y to ignore if the player is jumping -x
  Move( {direction.x, direction.y} );

  if (fabs(m_distance.x) < m_distanceToAttack) {
    if (fabs(m_distance.y) > 5.0f){
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
  if (!m_isIdle) return;
  glm::vec2 position = {transform.GetDepthPosition().x, transform.GetDepthPosition().y};

  // Calculates the point the enemy will go back to -x
  if (m_separateDirection.x == 0 && m_separateDirection.y == 0) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> distrib_x( 0, 30);
    std::uniform_int_distribution<> distrib_y(-15,  15);

    m_separateDirection.x = (m_player->transform.GetDepthPosition().x);
    if (m_separateDirection.x - position.x >= 0) m_separateDirection.x -= m_distanceToAttack + static_cast<float>(distrib_x(gen));
    else m_separateDirection.x += m_distanceToAttack - static_cast<float>(distrib_x(gen));
    m_separateDirection.y = (m_player->transform.GetDepthPosition().y + static_cast<float>(distrib_y(gen)));

    // Avoid SEPARATE state if point is out of bounds -x
    if (!m_sceneBoundsPoly->IsPointInside(m_separateDirection)) {
      m_state = FOLLOW;
      return;
    }
  }

  Move(glm::normalize(m_separateDirection - position));
  if (glm::distance(position, m_separateDirection) < 1.0f) {
    m_separateDirection = {0.0f, 0.0f};
    m_state = FOLLOW;
  }

  // TODO: THIS IS BROKEN
  // Swaps the sprite if not facing the same way -x
  // if ((direction.x <= 0) != (transform.relativeScale.x <= 0)) {
  //   transform.relativeScale.x *= -1;
  // }
}

void Enemy::OnRandomSparce() {
  if (!m_isIdle) return;
  glm::vec2 position = {transform.GetDepthPosition().x, transform.GetDepthPosition().y};

  if (m_separateDirection.x == 0.0f && m_separateDirection.y == 0.0f) {
    auto playerScale = m_player->transform.scale;
    auto playerPosition = m_player->transform.position;

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> distrib_x(-playerScale.x * 2, playerScale.x * 2);
    std::uniform_int_distribution<> distrib_y(-playerScale.y, playerScale.y);

    m_separateDirection = { playerPosition.x + distrib_x(gen), playerPosition.y + distrib_y(gen) };

    // Avoid SEPARATE state if point is out of bounds -x
    if (!m_sceneBoundsPoly->IsPointInside(m_separateDirection)) {
      m_separateDirection = {0.0f, 0.0f};
      OnRandomSparce();
      return;
    }
  }

  Move(glm::normalize(m_separateDirection - position));
  if (glm::distance(position, m_separateDirection) < 1.0f) {
    m_separateDirection = {0.0f, 0.0f};
    SetWait(0.5f, FOLLOW);
  }

  // Swaps the sprite if not facing the same way -x
  if ((glm::normalize(m_separateDirection - position).x >= 0) != (transform.relativeScale.x >= 0)) {
    transform.relativeScale.x *= -1;
  }
}

void Enemy::OnAttack() {
  if (m_isIdle) {
    if (fabs(m_distance.x) < (m_distanceToAttack - 20.0f)) {
      m_state = SEPARATE;
    }
    if (fabs(m_distance.x) > m_distanceToAttack || fabs(m_distance.y) > 5.0f) {
      m_state = FOLLOW;
    }
  }

  BasicAttack();
}

void Enemy::OnDead() {
  GET_FACTORY->DestroyObject(m_debugCol->GetId());
  GET_FACTORY->DestroyObject(GetId());
}

void Enemy::Destroy() { Character::Destroy(); }

}
