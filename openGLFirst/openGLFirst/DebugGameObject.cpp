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


  physics_->SetAcceleration(PhysicsComponent::Gravity);
  //GetTransform().SetRotation(45.0f);
  //GetTransform().SetPosition(glm::vec2(1.0f, 0.0f));
  GetTransform().SetScale(glm::vec2(0.1f, 0.1f));

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
  //physics_->SetVelocity(glm::vec2( 0.0f, 0.0f ));
  physics_->GetVelocity().x = 0;
}

void DebugGameObject::WKeyPress()
{
  //glm::vec2 moveDir(0.0f, 1.0f);

  glm::vec2 velo = physics_->GetVelocity();
  physics_->SetVelocity({ velo.x, 1.0f });

  //DirectionalMovement(moveDir);
}

void DebugGameObject::SKeyPress()
{
  //glm::vec2 velo = physics_->GetVelocity();
  //physics_->SetVelocity({ velo.x, -1.0f });
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

void DebugGameObject::OnCollisionUpdate(CollisionComponent::CollidingWithList&)
{
  //glm::vec2 velo = physics_->GetVelocity();
  //physics_->SetVelocity({ velo.x, -velo.y });
  //physics_->SetAcceleration({ 0,0 });
  GetTransform().SetPosition(GetTransform().GetPosition() + collision_->GetMTV());

  physics_->GetVelocity().y = 0.0f;

}

void DebugGameObject::OnCollision(CollisionComponent* otherCollider)
{
  //CollisionComponent::CollisionInformation collInfo = collision_->RetrieveCollisionInformation(otherCollider);

  std::cout << "Intersecting : " << collision_->GetMTV().x << " : " << collision_->GetMTV().y << std::endl;
}

void DebugGameObject::OnExitCollision(CollisionComponent* otherCollider)
{
  
}

