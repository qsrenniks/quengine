#include "stdafx.h"
#include "PhysicsComponent.h"
#include "IGameObject.h"
#include "Transform.h"

//PhysicsConstants
glm::vec2 PhysicsComponent::Gravity = glm::vec2(0.0f, -3.0f);

PhysicsComponent::PhysicsComponent()
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
  if (frozen_) return;

  Transform& transformComp = GetParent()->GetTransform();

  glm::vec2 translation{0};

  velocity_ = velocity_ + (acceleration_ * dt);

  translation = (velocity_ * dt) + transformComp.GetPosition();

  transformComp.SetPosition(glm::vec2(translation));
}

void PhysicsComponent::Draw()
{
  //do nothing. nothing needs to be drawn here.
}

bool PhysicsComponent::GetFrozen()
{
  return frozen_;
}

void PhysicsComponent::Freeze()
{
  frozen_ = true;
}

void PhysicsComponent::UnFreeze()
{
  frozen_ = false;
}

void PhysicsComponent::SetAcceleration(const glm::vec2& newAcceleration)
{
  acceleration_ = newAcceleration;
}

void PhysicsComponent::SetVelocity(const glm::vec2& newVelocity)
{
  velocity_ = newVelocity;
}

glm::vec2& PhysicsComponent::GetVelocity()
{
  return velocity_;
}
