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
#include "BPCollisionProfile.h"

DebugGameObject::DebugGameObject()
{
  sprite_->SetColor(glm::vec4(1.0f, 0.0f, 0.0f, 1.0f));
  AddComponent<RigidBodyComponent>(rigidBodyComponent_, 0.0f);

  //GetTransform().SetScale(0.5f, 0.5f);

  //rigidBodyComponent_->GetPhysicsComponent()->SetMass(1.0f);
  //rigidBodyComponent_->GetPhysicsComponent()->AddForceGenerator(new GravityForceGenerator());
  PhysicsComponent::ForceGeneratorRegistry.RegisterForceGenerator(rigidBodyComponent_->GetPhysicsComponent(), new GravityForceGenerator());
  rigidBodyComponent_->GetPhysicsComponent()->SetVelocityDecay(0.97f);

  InputSystem* inSystem = Engine::Instance()->GetInputSystem();
  auto& a = inSystem->AddInputAction("Move Up", this, &DebugGameObject::WKeyPress);
  //TODO: switch this to true for juming
  a.consumeInput_ = true;
  inSystem->AddInputAction("Move Left", this, &DebugGameObject::AKeyPress);
  inSystem->AddInputAction("Move Right", this, &DebugGameObject::DKeyPress);
  inSystem->AddInputAction("Move Down", this, &DebugGameObject::SKeyPress );

  rigidBodyComponent_->onCollisionEnter_.AddFunction(this, &DebugGameObject::OnCollisionEnter);
  rigidBodyComponent_->onCollisionExit_.AddFunction(this, &DebugGameObject::OnCollisionExit);
  rigidBodyComponent_->GetCollisionComponent()->GetBPCollisionProfile()->SetAABBExtent(glm::vec2(0.75f, 0.75f));

  Engine::Instance()->OnMousePress_.AddFunction(this, &DebugGameObject::OnMousePress);
}

DebugGameObject::~DebugGameObject()
{
  //here is where we need to RemoveFunction from the delegates that have been touched
  InputSystem *inSystem = Engine::Instance()->GetInputSystem();
  inSystem->RemoveInputAction("Move Up", this, &DebugGameObject::WKeyPress);
  inSystem->RemoveInputAction("Move Left", this, &DebugGameObject::AKeyPress);
  inSystem->RemoveInputAction("Move Right", this, &DebugGameObject::DKeyPress);
  inSystem->RemoveInputAction("Move Down", this, &DebugGameObject::SKeyPress);

  rigidBodyComponent_->onCollisionEnter_.RemoveFunction(this, &DebugGameObject::OnCollisionEnter);
  rigidBodyComponent_->onCollisionExit_.RemoveFunction(this, &DebugGameObject::OnCollisionExit);
}

void DebugGameObject::Update(float dt)
{
}

constexpr static float jumpHeight = 15.0f;
constexpr static float translationalSpeed = 10;
void DebugGameObject::WKeyPress()
{
  glm::vec2 dir(0.0f, translationalSpeed);
  rigidBodyComponent_->GetPhysicsComponent()->AddImpulse(dir);

  //GetTransform().SetScale(GetTransform().GetScale()*2.0f);
}

void DebugGameObject::SKeyPress()
{
  glm::vec2 dir(0.0f, -translationalSpeed);
  rigidBodyComponent_->GetPhysicsComponent()->AddForce(dir);

  DestroyGameObject();
}

void DebugGameObject::AKeyPress()
{
  glm::vec2 dir(-translationalSpeed, 0.0f);

  rigidBodyComponent_->GetPhysicsComponent()->AddForce(dir);
}

void DebugGameObject::OnMousePress(glm::vec2 mousePosition)
{
  //spawn arrow that has a set velocity and also ignores collision from the player
}

void DebugGameObject::DKeyPress()
{
  glm::vec2 dir(translationalSpeed, 0.0f);

  rigidBodyComponent_->GetPhysicsComponent()->AddForce(dir);
}

void DebugGameObject::OnCollisionEnter(RigidBodyComponent* otherObject)
{
  std::cout << "On Collision Enter" << std::endl;
}

void DebugGameObject::OnCollisionExit(RigidBodyComponent* otherObject)
{
  std::cout << "On Collision Exit" << std::endl;
}


