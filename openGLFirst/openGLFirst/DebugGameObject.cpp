#include "stdafx.h"
#include "DebugGameObject.h"
#include "SpriteComponent.h"
#include "CollisionComponent.h"
#include <iostream>
#include "Engine.h"
#include "InputSystem.h"
#include <string>
#include "PhysicsComponent.h"

#include <glm/gtc/matrix_transform.hpp>

//engine commands
#include "EngineCmder.h"

std::string DebugGameObject::DebugGameObjectName = "DebugGameObject";

DebugGameObject::DebugGameObject()
  : IGameObject(DebugGameObjectName)
{
  AddComponent<SpriteComponent>(sprite_, "vertexShader.vs", "fragmentShader.fs", glm::vec4{ 1.0f, 1.0f, 0.0f, 1.0f }, 0, 1.0f, 1.0f);
  AddComponent<PhysicsComponent>(physics_);
  AddComponent<CollisionComponent>(collision_, new SquareCollisionProfile(), new PhysicalResponse(physics_, false, 1.0f, 0.0f, 1.0f));
  //AddComponent<CollisionComponent>(collision_, new SquareCollisionProfile(), new DebugResponse());
   
  //physics_->SetAcceleration(PhysicsComponent::Gravity);
  GetTransform().SetScale(glm::vec2(0.1f, 0.1f));
  //GetTransform().SetPosition(glm::vec2(-0.30f, 0.15f));

  InputSystem* inSystem = Engine::Instance()->GetInputSystem();
  inSystem->AddInputAction("Move Up", this, &DebugGameObject::WKeyPress);
  inSystem->AddInputAction("Move Down", this, &DebugGameObject::SKeyPress);
  inSystem->AddInputAction("Move Left", this, &DebugGameObject::AKeyPress);
  inSystem->AddInputAction("Move Right", this, &DebugGameObject::DKeyPress);

  collision_->onEnterOverlap_.AddFunction(this, &DebugGameObject::OnCollision);
  collision_->onUpdateOverlap_.AddFunction(this, &DebugGameObject::OnCollisionUpdate);
  collision_->onExitOverlap_.AddFunction(this, &DebugGameObject::OnExitCollision);
}

DebugGameObject::~DebugGameObject()
{
}

IGameObject* DebugGameObject::Clone()
{ 
  return new DebugGameObject();
}

void DebugGameObject::Update(float dt)
{
  physics_->SetVelocity(glm::vec2( 0.0f, 0.0f ));
  //physics_->GetVelocity().x = 0.0f;
}

void DebugGameObject::WKeyPress()
{
  glm::vec2 velo = physics_->GetVelocity();
  physics_->SetVelocity({ velo.x, 1.0f });
}

void DebugGameObject::SKeyPress()
{
  glm::vec2 velo = physics_->GetVelocity();
  physics_->SetVelocity({ velo.x, -1.0f });
}

void DebugGameObject::AKeyPress()
{
  glm::vec2 velo = physics_->GetVelocity();
  physics_->SetVelocity({  -1.0f, velo.y});
}

void DebugGameObject::DKeyPress()
{
   glm::vec2 velo = physics_->GetVelocity();
  physics_->SetVelocity({  1.0f, velo.y });
}

//physics sets the new position and then using the old mtv for the previous collision information it moves the object an insufficient amount given the velocity for the objects
void DebugGameObject::OnCollisionUpdate(CollisionOccurence otherCollider)
{
}

void DebugGameObject::OnCollision(CollisionOccurence otherCollider)
{
  //std::cout << "On Collision Enter" << std::endl;
}

void DebugGameObject::OnExitCollision(CollisionOccurence otherCollider)
{
  //std::cout << "On Collision Exit" << std::endl;  
}

