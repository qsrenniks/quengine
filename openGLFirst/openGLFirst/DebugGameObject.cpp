#include "DebugGameObject.h"
#include "SpriteComponent.h"
#include <glad/glad.h>
#include <GLFW\glfw3.h>
#include <iostream>
#include "Engine.h"
#include "InputSystem.h"
#include <string>
#include "PhysicsComponent.h"
#include <glm/gtc/matrix_transform.hpp>

DebugGameObject::DebugGameObject()
{
  sprite_ = std::make_unique<SpriteComponent>("vertexShader.vs", "fragmentShader.fs", glm::vec4{ 1.0f, 1.0f, 0.0f, 1.0f });
  physics_ = std::make_unique<PhysicsComponent>();

  AddComponent(sprite_.get());
  AddComponent(physics_.get());

  InputSystem* inSystem = Engine::Instance()->GetSystem<InputSystem>();

  inSystem->AddInputAction("Move Up", this, &DebugGameObject::WKeyPress);
  inSystem->AddInputAction("Move Down", this, &DebugGameObject::SKeyPress);
  inSystem->AddInputAction("Move Left", this, &DebugGameObject::AKeyPress);
  inSystem->AddInputAction("Move Right", this, &DebugGameObject::DKeyPress);

  GetTransform() = glm::scale(glm::mat4(1.0f), glm::vec3{ 0.25f });

  physics_->SetAcceleration({ 0.0f, 0.0f, 0.0f });
}

DebugGameObject::~DebugGameObject()
{
}

void DebugGameObject::Update(float dt)
{
  physics_->SetVelocity({ 0.0f, 0.0f, 0.0f });
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


