#include "stdafx.h"
#include "PhysicsComponent.h"
#include "IGameObject.h"

PhysicsComponent::PhysicsComponent()
  //: IComponent(IComponent::Physics)
  : velocity_(0)
  , acceleration_({0})
{
}

//void PhysicsComponent::Draw()
//{
//
//}

void PhysicsComponent::Update(float dt)
{
  glm::mat4& transformComp = GetParent()->GetTransform();

  glm::vec3 translation{0};

  velocity_ = velocity_ + (acceleration_ * dt);

  translation = (velocity_ * dt) + glm::vec3(transformComp[3]);

  transformComp[3] = glm::vec4(translation, 1.0f);

  //resets the objects variables 
}

void PhysicsComponent::Draw()
{
  //do nothing. nothing needs to be drawn here.
}

void PhysicsComponent::SetAcceleration(const glm::vec3& newAccleration)
{
  acceleration_ = newAccleration;
}

void PhysicsComponent::SetVelocity(const glm::vec3& newVelocity)
{
  velocity_ = newVelocity;
}

glm::vec3& PhysicsComponent::GetVelocity()
{
  return velocity_;
}
