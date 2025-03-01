//
// Created by Alexey on 15/02/2025.
//

#include "Box.hpp"
#include "Core.hpp"
#include "Factory.hpp"
#include "Objects/Pickups/Pickup.hpp"

namespace game {
void Box::Init() {
  //Calls actor init because we don't need the default collider in damageable
  Actor::Init();

  //Sanity check
  if (m_jsonPath.empty() || m_pickupJsonPath.empty())
    return;

  //File open
  std::fstream bfile(m_jsonPath);
  std::fstream pfile(m_pickupJsonPath);

  //Sanity check
  if (!bfile.is_open()) {
    std::cout << "[Box] " << GetName() << " failed to open JSON file" << m_jsonPath << '\n';
    return;
  } if (!pfile.is_open()) {
    std::cout << "[Box] " << GetName() << " failed to open JSON file" << m_pickupJsonPath << '\n';
    return;
  }

  //Parsing
  std::cout << "[Box] " << GetName() << " Loading JSON file: " << m_jsonPath << '\n';
  Sigma::json_t Jb = Sigma::json_t::parse(bfile);
  std::cout << "[Box] " << GetName() << " Loading JSON file: " << m_pickupJsonPath << '\n';
  Sigma::json_t Jp = Sigma::json_t::parse(pfile);

  //File close
  bfile.close();
  pfile.close();

  //Box Variable Initialization
  m_texture = Jb["texture"];
  m_brokenTexture = Jb["brokenTexture"];
  m_health = Jb["health"];
  m_size= {Jb["size"]["x"], Jb["size"]["y"], Jb["size"]["z"] };

  //Pickup Variable Initialization
  m_pickupTexture = Jp["texture"];
  m_pickupHeal= Jp["heal"];
  m_pickupSize = {Jp["size"]["x"], Jp["size"]["y"], Jp["size"]["z"] };

  //Json clear
  std::cout << "[Box] " << GetName() << " JSON files loaded\n";
  Jb.clear();
  Jp.clear();

  //Setting Variables
  transform.scale = {m_size.x, m_size.y};
  m_collider = std::make_unique<Sigma::Collision::BoxCollider>(Sigma::Collision::PLAYER, Sigma::Collision::COLLISION);
  m_collider->box.Set(m_size);
  SetMaxHealth(m_health);
  SetTexture(m_texture.c_str());
}

void Box::OnDed() {
  SetTexture(m_brokenTexture.c_str());
  m_collider->enabled = false;
  auto Pi = GET_FACTORY->CreateObject<Pickup>("Pickup");
  Pi->SetColSize(m_pickupSize);
  Pi->SetHeal(m_pickupHeal);
  Pi->SetTexture(m_pickupTexture.c_str());
  Pi->transform.scale = {m_pickupSize.x, m_pickupSize.y};
  Pi->transform.position = transform.position;
}

}
