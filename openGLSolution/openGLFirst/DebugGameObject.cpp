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

  //rigidBodyComponent_->GetPhysicsComponent()->SetMass(1.0f);
  //rigidBodyComponent_->GetPhysicsComponent()->AddForceGenerator(new GravityForceGenerator());
  //rigidBodyComponent_->GetPhysicsComponent()->SetVelocityDecay(0.95f);

  InputSystem* inSystem = Engine::Instance()->GetInputSystem();
  auto& a = inSystem->AddInputAction("Move Up", this, &DebugGameObject::WKeyPress);
  //TODO: switch this to true for juming
  a.consumeInput_ = false;
  inSystem->AddInputAction("Move Left", this, &DebugGameObject::AKeyPress);
  inSystem->AddInputAction("Move Right", this, &DebugGameObject::DKeyPress);
  inSystem->AddInputAction("Move Down", this, &DebugGameObject::SKeyPress );
}

DebugGameObject::~DebugGameObject()
{
}

void DebugGameObject::Update(float dt)
{
}

constexpr static float jumpHeight = 15.0f;
constexpr static float translationalSpeed = 10;
void DebugGameObject::WKeyPress()
{
  glm::vec2 dir(0.0f, translationalSpeed);
  rigidBodyComponent_->GetPhysicsComponent()->AddForce(dir);
}

void DebugGameObject::SKeyPress()
{
  glm::vec2 dir(0.0f, -translationalSpeed);
  rigidBodyComponent_->GetPhysicsComponent()->AddForce(dir);
}

void DebugGameObject::AKeyPress()
{
  glm::vec2 dir(-translationalSpeed, 0.0f);

  rigidBodyComponent_->GetPhysicsComponent()->AddForce(dir);
}

void DebugGameObject::DKeyPress()
{
  glm::vec2 dir(translationalSpeed, 0.0f);

  rigidBodyComponent_->GetPhysicsComponent()->AddForce(dir);
}

