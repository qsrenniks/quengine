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
#include "RigidBodyComponent.h"

DebugGameObject::DebugGameObject()
{
  sprite_->SetColor(glm::vec4(1.0f, 0.0f, 0.0f, 1.0f));
  AddComponent<RigidBodyComponent>(rigidBodyComponent_, 0.0f);

  GetTransform().SetScale(0.5f, 0.5f);

  rigidBodyComponent_->GetPhysicsComponent()->SetMass(1.0f);
  //rigidBodyComponent_->GetPhysicsComponent()->AddForceGenerator(new GravityForceGenerator());
  //rigidBodyComponent_->GetPhysicsComponent()->SetVelocityDecay(0.95f);

  InputSystem* inSystem = Engine::Instance()->GetInputSystem();
  auto& a = inSystem->AddInputAction("Move Up", this, &DebugGameObject::WKeyPress);
  a.consumeInput_ = false;
  inSystem->AddInputAction("Move Down", this, &DebugGameObject::SKeyPress);
  inSystem->AddInputAction("Move Left", this, &DebugGameObject::AKeyPress);
  inSystem->AddInputAction("Move Right", this, &DebugGameObject::DKeyPress);

  rigidBodyComponent_->onCollisionEnter_.AddFunction(this, &DebugGameObject::OnCollisionEnter);
  rigidBodyComponent_->onCollisionExit_.AddFunction(this, &DebugGameObject::OnCollisionExit);
}

DebugGameObject::~DebugGameObject()
{
}

void DebugGameObject::Update(float dt)
{
  //physics_->SetVelocityX(0);
  //std::cout << GetTransform().GetPosition().x << ":" << GetTransform().GetPosition().y << std::endl;
  //Engine::Instance()->GetViewTransform().SetPosition(-GetTransform().GetPosition());
  //rigidBodyComponent_->GetPhysicsComponent()->SetVelocity(glm::vec2(0.0f, -200.0f));
}

constexpr static float jumpHeight = 250.0f;
constexpr static float moveSpeed = 1000;
void DebugGameObject::WKeyPress()
{
  glm::vec2 dir(0.0f, moveSpeed);
  //rigidBodyComponent_->GetPhysicsComponent()->SetVelocity(dir);
  //glm::vec2 pos = transform_.GetPosition();
  //transform_.SetPosition(pos + dir);

  rigidBodyComponent_->GetPhysicsComponent()->AddForce(dir);
}

void DebugGameObject::SKeyPress()
{
  //glm::vec2 velo = physics_->GetVelocity();
  //physics_->SetVelocity({ velo.x, -moveSpeed });
  glm::vec2 dir(0.0f, -moveSpeed);
  //rigidBodyComponent_->GetPhysicsComponent()->SetVelocity(dir);
  rigidBodyComponent_->GetPhysicsComponent()->AddForce(dir);
  //glm::vec2 pos = transform_.GetPosition();
  //transform_.SetPosition(pos + dir);

}

void DebugGameObject::AKeyPress()
{
  glm::vec2 dir(-moveSpeed, 0.0f);
  //rigidBodyComponent_->GetPhysicsComponent()->SetVelocity(dir);
  rigidBodyComponent_->GetPhysicsComponent()->AddForce(dir);

  //glm::vec2 pos = transform_.GetPosition();
  //transform_.SetPosition(pos + dir);

}

void DebugGameObject::OnCollisionEnter(RigidBodyComponent* otherBody)
{
  std::cout << "On Collision Enter" << std::endl;
}

void DebugGameObject::OnCollisionExit(RigidBodyComponent* otherBody)
{
  std::cout << "On Collision Exit" << std::endl;
}

void DebugGameObject::DKeyPress()
{
  glm::vec2 dir(moveSpeed, 0.0f);
  //rigidBodyComponent_->GetPhysicsComponent()->SetVelocity(dir);
  rigidBodyComponent_->GetPhysicsComponent()->AddForce(dir);
  //glm::vec2 pos = transform_.GetPosition();
  //transform_.SetPosition(pos + dir);

}

void DebugGameObject::OnCollision(const CollisionOccurence& otherCollider)
{
  std::cout << "On Collision Enter" << std::endl;
}

void DebugGameObject::OnExitCollision(const CollisionOccurence& otherCollider)
{
  std::cout << "On Collision Exit" << std::endl;  
}

