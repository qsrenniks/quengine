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

  //GetTransform().SetRotation(45.0f);
  GetTransform().SetPosition(glm::vec2(1.0f, 0.0f));
  GetTransform().SetScale(glm::vec2(0.1f, 0.1f));

  InputSystem* inSystem = Engine::Instance()->GetInputSystem();
  inSystem->AddInputAction("Move Up", this, &DebugGameObject::WKeyPress);
  inSystem->AddInputAction("Move Down", this, &DebugGameObject::SKeyPress);
  inSystem->AddInputAction("Move Left", this, &DebugGameObject::AKeyPress);
  inSystem->AddInputAction("Move Right", this, &DebugGameObject::DKeyPress);


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
}

void DebugGameObject::WKeyPress()
{
  physics_->GetVelocity().y = 1.0f;
}

void DebugGameObject::SKeyPress()
{
  physics_->GetVelocity().y = -1.0f;
}

void DebugGameObject::AKeyPress()
{
  physics_->GetVelocity().x = -1.0f;
}

void DebugGameObject::DKeyPress()
{
  physics_->GetVelocity().x = 1.0f;
}


