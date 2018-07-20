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

  GetTransform().SetScale(glm::vec2(0.1f, 0.1f));
  //physics_->SetAcceleration(PhysicsComponent::Gravity);


  physics_->SetBounce(0.0f);
  physics_->SetMass(1.0f);
  physics_->SetFriction(0.0f);
  //physics_->SetVelocityY(-1.0f); 
  physics_->SetVelocityDecay(0.8f);

  InputSystem* inSystem = Engine::Instance()->GetInputSystem();
  inSystem->AddInputAction("Move Up", this, &DebugGameObject::WKeyPress);
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
}

#define SPEED 0.5f
void DebugGameObject::WKeyPress()
{
  glm::vec2 velo = physics_->GetVelocity();
  physics_->SetVelocity({ velo.x, SPEED });
}

void DebugGameObject::SKeyPress()
{
  glm::vec2 velo = physics_->GetVelocity(); 
  physics_->SetVelocity({ velo.x, -SPEED });
}

void DebugGameObject::AKeyPress()
{
  glm::vec2 velo = physics_->GetVelocity();
  physics_->SetVelocity({  -SPEED, velo.y});
}

void DebugGameObject::DKeyPress()
{
   glm::vec2 velo = physics_->GetVelocity();
  physics_->SetVelocity({ SPEED, velo.y });
}

void DebugGameObject::OnCollision(const CollisionOccurence& otherCollider)
{
  std::cout << "On Collision Enter" << std::endl;
}

void DebugGameObject::OnExitCollision(const CollisionOccurence& otherCollider)
{
  std::cout << "On Collision Exit" << std::endl;  
}

