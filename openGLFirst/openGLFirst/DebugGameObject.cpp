#include "stdafx.h"
#include "DebugGameObject.h"
#include "SpriteComponent.h"
#include "CollisionComponent.h"
#include <iostream>
#include "Engine.h"
#include "InputSystem.h"
#include <string>
#include "PhysicsComponent.h"
#include "TextLibrary.h"

#include <glm/gtc/matrix_transform.hpp>
#include "CollisionOccurence.h"

//engine commands
#include "EngineCmder.h"

DebugGameObject::DebugGameObject()
{
  sprite_->SetColor(glm::vec4(1.0f, 0.0f, 0.0f, 1.0f));

  GetTransform().SetScale(0.5f, 0.5f);

  //physics_->AddForceGenerator(new GravityForceGenerator());

  physics_->SetBounce(0.0f);
  physics_->SetMass(1.0f);
  //physics_->SetVelocityDecay(0.95f);

  InputSystem* inSystem = Engine::Instance()->GetInputSystem();
  auto& a = inSystem->AddInputAction("Move Up", this, &DebugGameObject::WKeyPress);
  a.consumeInput_ = false;
  inSystem->AddInputAction("Move Down", this, &DebugGameObject::SKeyPress);
  inSystem->AddInputAction("Move Left", this, &DebugGameObject::AKeyPress);
  inSystem->AddInputAction("Move Right", this, &DebugGameObject::DKeyPress);
}

DebugGameObject::~DebugGameObject()
{
}

void DebugGameObject::Update(float dt)
{
  //physics_->SetVelocityX(0);
  //std::cout << GetTransform().GetPosition().x << ":" << GetTransform().GetPosition().y << std::endl;
  Engine::Instance()->GetViewTransform().SetPosition(-GetTransform().GetPosition());
  physics_->SetVelocity(glm::vec2(0.0f, -200.0f));
}

constexpr static float jumpHeight = 250.0f;
constexpr static float moveSpeed = 100.0f;
void DebugGameObject::WKeyPress()
{
  glm::vec2 dir(0.0f, moveSpeed);
  physics_->SetVelocity(dir);
}

void DebugGameObject::SKeyPress()
{
  //glm::vec2 velo = physics_->GetVelocity();
  //physics_->SetVelocity({ velo.x, -moveSpeed });
  glm::vec2 dir(0.0f, -moveSpeed);
  physics_->SetVelocity(dir);
}

void DebugGameObject::AKeyPress()
{
  glm::vec2 dir(-moveSpeed, 0.0f);
  physics_->SetVelocity(dir);
}

void DebugGameObject::DKeyPress()
{
  glm::vec2 dir(moveSpeed, 0.0f);
  physics_->SetVelocity(dir);
}

void DebugGameObject::OnCollision(const CollisionOccurence& otherCollider)
{
  std::cout << "On Collision Enter" << std::endl;
}

void DebugGameObject::OnExitCollision(const CollisionOccurence& otherCollider)
{
  std::cout << "On Collision Exit" << std::endl;  
}

