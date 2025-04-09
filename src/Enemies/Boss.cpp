#include "Boss.hpp"

#include "AnimationSystem/AnimationSystem.hpp"
#include "BigEnemy.hpp"
#include "Core.hpp"
#include "DefaultEnemy.hpp"
#include "Enemies/Proj.hpp"
#include "Factory.hpp"
#include "GrabEnemy.hpp"
#include "Objects/Pickups/Pickup.hpp"
#include "Random.hpp"
#include "TntEnemy.hpp"
#include "aecore/imgui/imgui.h"
#include "glm/fwd.hpp"
#include "glm/geometric.hpp"

namespace game {

void Boss::DebugWindow() {
  Enemy::DebugWindow();
  ImGui::DragInt("Current State", &m_currentState);
  ImGui::DragInt("Next State", &m_nextState);
  ImGui::Value("TIMER", m_timer);
}
void Boss::Update(double delta) {
  Enemy::Update(delta);
  m_timer += delta;
  m_player = GetNearestPlayer();
  if (!m_phaseDose && m_health <= m_maxHealth / 2) {
    m_phaseDose = true;
    Transition();
  }
  if (m_currentState == 49 && m_timer >= 3) {
    m_taunt = false;
    m_invincible = false;
  }
  if (m_animComp->GetCurrentAnimation()->name == "Taunt") {
    m_health += 20.0 * delta;
    m_bar->m_currentHealth = GetHealth();
  }
}

Boss::Boss(const Sigma::id_t id, const char *jsonPath) : Enemy(id, jsonPath) {
  glm::vec2 scale = {1024, 80};
  glm::vec3 pos = {0.0f, -400.0f, 0.0f};

  m_barBackground = GET_FACTORY->CreateObject<Sigma::UIImage>("Boss Health Background", "BossbarBackground");
  m_barBackground->m_screenSpaceTransform.position = pos;
  m_barBackground->m_screenSpaceTransform.scale = scale;
  m_bar = GET_FACTORY->CreateObject<HealthBar>("Boss Health Bar", "BossbarRed");
  m_bar->m_maxHealth = 100;
  m_bar->m_currentHealth = 100;
  m_bar->m_screenSpaceTransform.position = pos + glm::vec3{-scale.x / 2, 0, 0};
  m_bar->SetScale(scale);
  m_bar->SetAlignment(Sigma::UIProgressBar::LEFT);
  m_barBorder = GET_FACTORY->CreateObject<Sigma::UIImage>("Boss Health border", "BossbarRim");
  m_barBorder->m_screenSpaceTransform.position = pos;
  m_barBorder->m_screenSpaceTransform.scale = scale;
}

void Boss::Init() {
  Enemy::Init();
  m_restartTime = 2;
  auto anim = GET_ANIMATION->LoadTextureAtlas("assets/characters/presenter/Presenter1.json");
  m_animComp->SetTextureAtlas(anim);
  SetTexture(anim->textureStr.c_str());
  m_animComp->SetCurrentAnim("Idle");
  m_animComp->PlayAnim();

  m_animComp->SetupTrailEffect(20, .02f, .25f, glm::vec4(.7f, .4f, .6f, 1), glm::vec4(.7f, .4f, .6f, 0));

  // Setup player collider
  m_collider->box.Set(25, 25, 50, 50, 10, transform.offset);
  m_collider->SetColliderType(Sigma::Collision::COLLISION);
  m_collider->SetColliderFlags(Sigma::Collision::ENEMY);
  m_collider->damage = 1.0f;
  m_collider->SetOwner(this);

  m_defaultState = STATE_IDLE;
  m_nextState = STATE_IDLE;
  m_baseMaxSpeed = maxSpeed;
}

void Boss::Taunt() {
  m_animComp->SetCurrentAnim("Taunt");
  m_invincible = false;
}

void Boss::Start() {
  Enemy::Start();
  BindState(STATE_GOTO, [this] { GotoState(); });
  BindState(STATE_BASIC, [this] { BasicState(); });
  BindState(STATE_SPECIAL, [this] { SpecialState(); });
  BindState(STATE_PURSUE, [this] { Pursue(); });
  BindState(STATE_RETREAT, [this] { Retreat(); });
  BindState(-1, [this] {});
  BindState(49, [this]{Taunt();});

  m_bar->m_maxHealth = GetMaxHealth();
  m_bar->m_currentHealth = GetMaxHealth();
}

void Boss::Transition() {
  velocity = {};
  m_timer = 0;
  m_invincible = false;
  m_taunt = true;
  Taunt();
  m_animComp->SetCurrentAnim("Taunt");
  SetState(49);
  float health = m_health;
  m_jsonPath = "assets/characters/presenter/behaviour2.json";
  Serialize();
  m_baseMaxSpeed = maxSpeed;
  m_health = health;
}

bool Boss::IsInBounds(glm::vec2 pos) { return m_sceneBoundsPoly->IsPointInside(pos); }

void Boss::IdleState() {
  // if (!m_isDoingSomething)
  //   return;
  m_animComp->SetCurrentAnim("Idle");
  m_nextState = STATE_BASIC;
  SetState(STATE_PURSUE);
}

void Boss::GotoState() {
  if (!m_isDoingSomething)
    return;
  glm::vec2 position = (glm::vec2) transform.GetDepthPosition();
  glm::vec2 direction = glm::normalize(m_goto - position);
  if ((direction.x >= 0) != (transform.relativeScale.x >= 0)) {
    transform.relativeScale.x *= -1;
  }
  if (!IsInBounds(static_cast<glm::vec2>(transform.position) + (direction * 5.0f)) || glm::distance(position, m_goto) < 5.0f) {
    WaitSeconds(0.0f, m_nextState);
    return;
  }
  Move(direction);
  if (dash) {
    Dash();
    dash = false;
  }
  m_animComp->SetCurrentAnim("Walk");
}

void Boss::Pursue() {
  if (!m_isDoingSomething)
    return;
  m_animComp->SetCurrentAnim("Idle");

  do {
    m_goto = static_cast<glm::vec2>(m_player->transform.position) + (Sigma::Random::Circle() * 30.0f);
  } while (!IsInBounds(m_goto));

  WaitSeconds(.1f, STATE_GOTO);
}

void Boss::Retreat() {
  if (!m_isDoingSomething)
    return;
  m_consectutiveAttack = 0;
  m_animComp->SetCurrentAnim("Idle");

  do {
    if (m_player == nullptr)
      return;
    m_goto = static_cast<glm::vec2>(m_player->transform.position) + (Sigma::Random::Circle() * 150.0f);
  } while (!IsInBounds(m_goto));

  dash = true;
  SetState(STATE_GOTO);
}

void Boss::BasicState() {
  if (!m_isDoingSomething || m_player == nullptr)
    return;
  maxSpeed = m_baseMaxSpeed * 1.5f;
  glm::vec3 targets[2];
  if (m_player == nullptr)
    return;
  targets[0] = m_player->transform.position + glm::vec3(-50, 0, 0);
  targets[1] = m_player->transform.position + glm::vec3(50, 0, 0);
  m_goto = glm::distance(transform.position, targets[0]) < glm::distance(transform.position, targets[1]) ? targets[0]
                                                                                                         : targets[1];
  glm::vec2 position = (glm::vec2) transform.GetDepthPosition();
  float distance = glm::distance(position, m_goto);
  if (distance <= 10) {
    velocity = {};
    FacePlayer();
    BasicAttack();
  } else {

    dash = true;
    SetState(STATE_GOTO);
  }
}

void Boss::SpecialState() {
  if (!m_isDoingSomething)
    return;
  if (m_consectutiveAttack) {
    dash = false;
    SpecialOne();
    return;
  }
  glm::vec2 position = (glm::vec2) transform.GetDepthPosition();
  float distance = glm::distance(position, m_goto);
  if (distance <= 10) {
    dash = false;
    SpecialOne();
  } else if (m_consectutiveAttack == 0) {
    SetState(STATE_RETREAT);
  } else {
    dash = false;
    SpecialOne();
  }
}

void Boss::SpecialOne() {
  if (!m_isDoingSomething)
    return;
  FacePlayer();
  SuperAttack();
  m_consectutiveAttack++;
  std::shared_ptr<Proj> proj = GET_FACTORY->CreateObject<game::Proj>("Proj");
  proj->transform.position = transform.position + glm::vec3(0, 60, 0);
  proj->velocity =
      glm::normalize(proj->transform.position - (m_player->transform.position + glm::vec3(0, 55, 0))) * -200.0f;
  destructionQueue.push_back(proj);
  if (m_consectutiveAttack >= 3) {
    EndedMove();
  } else {
    WaitSeconds(0.3f, STATE_SPECIAL);
  }
}

void Boss::FacePlayer() {
  if (m_player == nullptr)
    return;
  glm::vec3 distance = m_player->transform.GetDepthPosition() - transform.GetDepthPosition();
  if ((distance.x >= 0) != (transform.relativeScale.x >= 0)) {
    transform.relativeScale.x *= -1;
  }
}

void Boss::OnFullComboPerformed(bool super) {
  if (super) {
    return;
  }
  m_timer = 0;
  m_basicCombo = 0;
  maxSpeed = m_baseMaxSpeed;
  m_consectutiveAttack = 0;

  if (m_nextState == STATE_SPECIAL) {
    m_nextState = STATE_BASIC;
    SetState(STATE_PURSUE);
    return;
  }

  if (rand() % 2 == 0) {
    m_nextState = STATE_SPECIAL;
    SetState(STATE_RETREAT);
  } else {
    m_nextState = STATE_BASIC;
    SetState(STATE_PURSUE);
  }
}

void Boss::SpawnWave1() {
  m_wave1 = true;
  auto m_gameplayManager = GameplayManager::GetInstance();

  auto e1 = GET_FACTORY->CreateObject<game::DefaultEnemy>("Enemy 1", "assets/characters/BasicEnemy/behaviour.json");
  auto e2 = GET_FACTORY->CreateObject<game::DefaultEnemy>("Enemy 1", "assets/characters/BasicEnemy/behaviour.json");

  e1->transform.position = glm::vec3{-100, -90, 90};
  e1->Enable(m_gameplayManager->GetPlayers());
  e1->SetSceneBoundsPoly(m_gameplayManager->GetSceneBoundsPoly());
  enemyDeletionQueue.push_back(e1);
  e2->transform.position = glm::vec3{-485, -90, 90};
  e2->Enable(m_gameplayManager->GetPlayers());
  e2->SetSceneBoundsPoly(m_gameplayManager->GetSceneBoundsPoly());
  enemyDeletionQueue.push_back(e2);
}

void Boss::SpawnWave2() {
  m_wave2 = true;
  auto m_gameplayManager = GameplayManager::GetInstance();

  auto e1 = GET_FACTORY->CreateObject<game::DefaultEnemy>("Enemy 1", "assets/characters/BasicEnemy/behaviour.json");
  auto e2 = GET_FACTORY->CreateObject<game::DefaultEnemy>("Enemy 1", "assets/characters/BasicEnemy/behaviour.json");
  auto e3 = GET_FACTORY->CreateObject<game::GrabEnemy>("Grab Enemy", "assets/characters/grabEnemy/behaviour.json");

  e1->transform.position = glm::vec3{-100, -90, 90};
  e1->Enable(m_gameplayManager->GetPlayers());
  e1->SetSceneBoundsPoly(m_gameplayManager->GetSceneBoundsPoly());
  enemyDeletionQueue.push_back(e1);
  e2->transform.position = glm::vec3{-485, -90, 90};
  e2->Enable(m_gameplayManager->GetPlayers());
  e2->SetSceneBoundsPoly(m_gameplayManager->GetSceneBoundsPoly());
  enemyDeletionQueue.push_back(e2);
  e3->transform.position = glm::vec3{-210, -140, 140};
  e3->Enable(m_gameplayManager->GetPlayers());
  e3->SetSceneBoundsPoly(m_gameplayManager->GetSceneBoundsPoly());
  enemyDeletionQueue.push_back(e3);

  m_pickups[0] = GET_FACTORY->CreateObject<Pickup>();
  m_pickups[1] = GET_FACTORY->CreateObject<Pickup>();
  m_pickups[0]->transform.position = glm::vec3{-575, -85, 85};
  m_pickups[0]->transform.scale = glm::vec2{25, 25};
  m_pickups[0]->SetColSize(glm::vec3{25, 25, 25});
  m_pickups[0]->SetHeal(50);
  m_pickups[0]->SetTexture("assets/objects/Hamburger.png");
  m_pickups[1]->transform.position = glm::vec3{0, -85, 85};
  m_pickups[1]->transform.scale = glm::vec2{25, 25};
  m_pickups[1]->SetColSize(glm::vec3{25, 25, 25});
  m_pickups[1]->SetHeal(50);
  m_pickups[1]->SetTexture("assets/objects/Hamburger.png");
}

void Boss::SpawnWave3() {
  m_wave3 = true;
  auto m_gameplayManager = GameplayManager::GetInstance();

  auto e1 = GET_FACTORY->CreateObject<game::DefaultEnemy>("Enemy 1", "assets/characters/BasicEnemy/behaviour.json");
  auto e2 = GET_FACTORY->CreateObject<game::DefaultEnemy>("Enemy 1", "assets/characters/BasicEnemy/behaviour.json");
  auto e3 = GET_FACTORY->CreateObject<game::BigEnemy>("Big Enemy", "assets/characters/bigEnemy/behaviour.json");
  auto e4 = GET_FACTORY->CreateObject<game::TntEnemy>("Tnt Enemy", "assets/characters/tntEnemy/behaviour.json");

  e1->transform.position = glm::vec3{-100, -90, 90};
  e1->Enable(m_gameplayManager->GetPlayers());
  e1->SetSceneBoundsPoly(m_gameplayManager->GetSceneBoundsPoly());
  enemyDeletionQueue.push_back(e1);
  e2->transform.position = glm::vec3{-485, -90, 90};
  e2->Enable(m_gameplayManager->GetPlayers());
  e2->SetSceneBoundsPoly(m_gameplayManager->GetSceneBoundsPoly());
  enemyDeletionQueue.push_back(e2);
  e3->transform.position = glm::vec3{-210, -140, 140};
  e3->Enable(m_gameplayManager->GetPlayers());
  e3->SetSceneBoundsPoly(m_gameplayManager->GetSceneBoundsPoly());
  enemyDeletionQueue.push_back(e3);
  e4->transform.position = glm::vec3{-315, -35, 35};
  e4->Enable(m_gameplayManager->GetPlayers());
  e4->SetSceneBoundsPoly(m_gameplayManager->GetSceneBoundsPoly());
  enemyDeletionQueue.push_back(e4);
}

void Boss::EndedMove() {
  if (m_hasDoneDamage && m_nextState == STATE_BASIC) {
    return;
  } else if (m_nextState == STATE_SPECIAL && m_consectutiveAttack != 3) {
    return;
  }
  OnFullComboPerformed(false);
}

void Boss::Destroy() {
  Enemy::Destroy();
  // Dante this is shit 0x (thanks -dante)
  while (!destructionQueue.empty()) {
    if (destructionQueue.back()) {
      GET_FACTORY->DestroyObject(destructionQueue.back());
    }
    destructionQueue.pop_back();
  }

  GET_FACTORY->DestroyObject(m_barBorder);
  GET_FACTORY->DestroyObject(m_bar);
  GET_FACTORY->DestroyObject(m_barBackground);

  for (auto& enemy: enemyDeletionQueue) {
    GET_FACTORY->DestroyObject(enemy);
    // enemy->OnDamage(Sigma::Damage::DamageEvent(enemy->GetId(),this,Sigma::Collision::DAMAGE, 100000, {0,0},Sigma::Damage::DamageType::DAMAGE));
  }
  enemyDeletionQueue.clear();

  if (!GetAlive())
    GameplayManager::GetInstance()->GotoNextScene();
}

void Boss::OnDamage(const Sigma::Damage::DamageEvent &e) {
  Enemy::OnDamage(e);

  if (e.GetOther() == this)
    return;
  
  OnFullComboPerformed(false);
  m_bar->m_currentHealth = GetHealth();

  if (GetHealth() / GetMaxHealth() <= 0.75f && !m_wave1)
    SpawnWave1();
  if (GetHealth() / GetMaxHealth() <= 0.5f && !m_wave2)
    SpawnWave2();
  if (GetHealth() / GetMaxHealth() <= 0.25f && !m_wave3)
    SpawnWave3();
}

} // namespace game
