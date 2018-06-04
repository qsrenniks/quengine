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
  //TransformComponent *transform = new TransformComponent();
  physics_ = std::make_unique<PhysicsComponent>();

  AddComponent(sprite_.get());
  //AddComponent(transform);
  AddComponent(physics_.get());

  InputSystem* inSystem = Engine::instance()->GetSystem<InputSystem>();

  inSystem->BindDelegate("Move Up", this, &DebugGameObject::WKeyPress);
  inSystem->BindDelegate("Move Down", this, &DebugGameObject::SKeyPress);
  inSystem->BindDelegate("Move Left", this, &DebugGameObject::AKeyPress);
  inSystem->BindDelegate("Move Right", this, &DebugGameObject::DKeyPress);

  GetTransform() = glm::scale(glm::mat4(1.0f), glm::vec3{0.25f});
}

DebugGameObject::~DebugGameObject()
{
}

void DebugGameObject::Update(float dt)
{
  //PhysicsComponent *physics = GetComponent<PhysicsComponent *>(IComponent::Physics);
  //TransformComponent *transform = GetComponent<TransformComponent *>(IComponent::Transform);

  if (GetTransform()[3].y < -0.5)
  {
    physics_->SetAcceleration({ 0, 0, 0 });
    physics_->SetVelocity({ 0, 0, 0 });
  }

  glm::vec4 modded = GetTransform()[3] * Engine::instance()->GetCameraTransform();
  //glm::translate()
  Engine::instance()->GetViewTransform()[3] = modded;
}

static float dt = 0.016667f;
void DebugGameObject::WKeyPress()
{
  //TransformComponent *transformComp = GetComponent<TransformComponent*>(IComponent::Transform);
  GetTransform()[3].y += dt;
}

void DebugGameObject::SKeyPress()
{
  //TransformComponent *transformComp = GetComponent<TransformComponent*>(IComponent::Transform);

  GetTransform()[3].y += -dt;
}

void DebugGameObject::AKeyPress()
{
  //TransformComponent *transformComp = GetComponent<TransformComponent*>(IComponent::Transform);

  GetTransform()[3].x += -dt;
}

void DebugGameObject::DKeyPress()
{
  //TransformComponent *transformComp = GetComponent<TransformComponent*>(IComponent::Transform);

  GetTransform()[3].x += dt;
}


