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

DebugGameObject::DebugGameObject()
{
  //TODO: change the component name to something in the base component class like pvars or something similar.
  AddComponent<SpriteComponent>(sprite_, "vertexShader.vs", "fragmentShader.fs", glm::vec4{ 1.0f, 1.0f, 0.0f, 1.0f }, 0, 1.0f, 1.0f);
  AddComponent<PhysicsComponent>(physics_);
  AddComponent<CollisionComponent>(collision_, new SquareCollisionProfile(collision_));


  //physics_->SetAcceleration(PhysicsComponent::Gravity);
  GetTransform().SetScale(glm::vec2(0.1f, 0.1f));

  //physics_->GetVelocity().y = -1.0f;

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
  //physics_->GetVelocity().y = 0.0f;
  //physics_->GetVelocity().x = 0.0f;

  //std::cout << "Velocity: " << physics_->GetVelocity().x << ": " << physics_->GetVelocity().y << std::endl;
  physics_->SetVelocity(glm::vec2( 0.0f, 0.0f ));

  //std::cout << " position : " << GetTransform().GetPosition().x << ": " << GetTransform().GetPosition().y << std::endl;
}

void DebugGameObject::WKeyPress()
{
  glm::vec2 velo = physics_->GetVelocity();
  physics_->SetVelocity({ velo.x, 1.0f });

  //GetTransform().SetPosition(GetTransform().GetPosition() + glm::vec2{ 0.0f, 0.01f });

  //GetTransform().GetPosition().y += 0.01f;

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

//CollisionOccurence DebugGameObject::GetCollisionOccurence()
//{
//  return collision_->GetCollisionOccurence();
//}

void DebugGameObject::DKeyPress()
{
   glm::vec2 velo = physics_->GetVelocity();
  physics_->SetVelocity({  1.0f, velo.y });
}

//physics sets the new position and then using the old mtv for the previous collision information it moves the object an insufficient amount given the velocity for the objects
void DebugGameObject::OnCollisionUpdate(CollisionOccurence otherCollider)
{
   //GetTransform().SetPosition(GetTransform().GetPosition() + GetCollisionOccurence().mtv_);
  //std::cout << "On Collision Update" << std::endl;
}

void DebugGameObject::OnCollision(CollisionOccurence otherCollider)
{
  //std::cout << "Intersecting : " << GetCollisionOccurence().mtv_.x << " : " << GetCollisionOccurence().mtv_.y << std::endl;
  std::cout << "On Collision Enter" << std::endl;
}

void DebugGameObject::OnExitCollision(CollisionOccurence otherCollider)
{
  std::cout << "On Collision Exit" << std::endl;  
}

