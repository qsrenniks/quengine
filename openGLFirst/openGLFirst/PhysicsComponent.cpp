#include "stdafx.h"
#include "PhysicsComponent.h"
#include "IGameObject.h"
#include "Transform.h"

//PhysicsConstants
glm::vec2 PhysicsComponent::Gravity = glm::vec2(0.0f, -1.0f);

PhysicsComponent::PhysicsComponent()
  : velocity_(0.0f, 0.0f)
  , acceleration_(0.0f, 0.0f)
  , rotationalVelocity_(0.0f)
{
}

//void PhysicsComponent::Draw()
//{
//
//}

void PhysicsComponent::Update(float dt)
{
  if (frozen_) return;

  //maybe this instead returns a direction that velocity should be clamped to 
  //if (GetParent()->PreventPhysics()) return; 

  Transform& transformComp = GetParent()->GetTransform();

  glm::vec2 translation{0};

  velocity_ = velocity_ + (acceleration_ * dt);

  //CollisionOccurence occ = GetParent()->GetCollisionOccurence();

  //if (occ.IsValid() == true)
  //{
  //  if (/*occ.collisionStatus_ == CollisionOccurence::CollisionStatus::COLLIDING ||*/ occ.collisionStatus_ == CollisionOccurence::CollisionStatus::TOUCHING)
  //  {
  //    //while (glm::dot(velocity_, occ.mtv_) < 0)
  //    //{
  //    //  velocity_ += occ.mtv_;
  //    //}

  //      //clamp the vector given the mtv
  //    float vectorMagnitude = glm::length(velocity_);

  //    glm::vec2 mtvNorm = glm::normalize(occ.mtv_);

  //    glm::vec2 vInDirOfMTV = occ.mtv_ * vectorMagnitude;

  //    velocity_ += vInDirOfMTV;

  //  }
  //}

  translation = (velocity_ * dt) + transformComp.GetPosition();

  transformComp.SetPosition(glm::vec2(translation));

  float rotation = transformComp.GetRotation();

  rotation += GetRotationalVelocity() * dt;

  transformComp.SetRotation(rotation);
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

const glm::vec2& PhysicsComponent::GetAcceleration() const
{
  return acceleration_;
}

void PhysicsComponent::SetVelocity(const glm::vec2& newVelocity)
{
  velocity_ = newVelocity;
}

glm::vec2& PhysicsComponent::GetVelocity()
{
  return velocity_;
}

void PhysicsComponent::SetRotationalVelocity(float val)
{
  rotationalVelocity_ = val;
}

void PhysicsComponent::SetIsStatic(bool isStatic) 
{
  isStatic_ = isStatic;
}

bool PhysicsComponent::GetIsStatic() const
{
  return isStatic_;
}

float PhysicsComponent::GetRotationalVelocity() const
{
  return rotationalVelocity_;
}
