#include "stdafx.h"
#include "PhysicsComponent.h"
#include "IGameObject.h"
#include "Transform.h"
#include "CollisionOccurence.h"
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/vector_angle.hpp>
#include <algorithm>
#include "Engine.h"

#include <iostream>
//PhysicsConstants

PhysicsComponent::PhysicsComponent()
  : velocity_(0.0f, 0.0f)
  , acceleration_(0.0f, 0.0f)
  , rotationalVelocity_(0.0f)
{
}
void PhysicsComponent::SetSimulatePhysics(bool simulate)
{
  simulatePhysics_ = simulate;
}

bool PhysicsComponent::GetSimulatePhysics()
{
  return simulatePhysics_;
}

void PhysicsComponent::Update(float dt)
{
  if (simulatePhysics_ == false) return;
  GatherForceGenerators();

  //lastFrameAcceleration_ = acceleration_ + (inverseMass_ * forces_);

  Transform& transform = GetParent()->GetTransform();

  velocityAtFrameStart_ = velocity_;

  velocity_ = velocity_ * glm::pow(velocityDecay_, dt) + acceleration_ * dt;

  acceleration_ = inverseMass_ * forces_;

  //lastFrameForce_ = forces_;

  glm::vec2 newPos = transform.GetPosition() + velocity_ * dt;

  transform.SetPosition(newPos);

  ResetForces();
}

void PhysicsComponent::Draw()
{
  //do nothing. nothing needs to be drawn here.
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
  if (simulatePhysics_ == false)
  {
    return;
  }

  velocity_ = newVelocity;
}

void PhysicsComponent::SetVelocityX(float x)
{
  velocity_.x = x;
}

void PhysicsComponent::SetVelocityY(float y)
{
  velocity_.y = y;
}

//const glm::vec2& PhysicsComponent::GetAccelerationLastFrame()
//{
//  return lastFrameAcceleration_;
//}

void PhysicsComponent::ZeroOutAcceleration()
{
  acceleration_.x = 0.0f;
  acceleration_.y = 0.0f;
}

float PhysicsComponent::GetMass()
{
  return mass_;
}

float PhysicsComponent::GetInverseMass()
{
  return inverseMass_;
}

const glm::vec2& PhysicsComponent::GetVelocity() const
{
  return velocity_;
}

const glm::vec2& PhysicsComponent::GetVelocityAtFrameStart() const
{
  return velocityAtFrameStart_;
}

void PhysicsComponent::SetRotationalVelocity(float val)
{
  rotationalVelocity_ = val;
}

void PhysicsComponent::SetMass(float mass)
{
  mass_ = mass;

  if (mass_ == 0.0f)
  {
    inverseMass_ = 0.0f;
  }
  else
  {
    inverseMass_ = 1 / mass_;
  }
}

void PhysicsComponent::SetVelocityDecay(float x )
{
  velocityDecay_ = x;
}

const glm::vec2& PhysicsComponent::GetForce()
{
  return forces_;
}

void PhysicsComponent::AddForce(glm::vec2& force)
{
  forces_ += force;
}

void PhysicsComponent::ResetForces()
{
  forces_.x = 0.0f;
  forces_.y = 0.0f;
}

void PhysicsComponent::AddImpulse(glm::vec2& impulse)
{
  velocity_ = velocity_ + inverseMass_ * impulse;
}

//const glm::vec2& PhysicsComponent::GetForceLastFrame()
//{
//  return lastFrameForce_;
//}

void PhysicsComponent::GatherForceGenerators()
{
  for (ForceGenerator* gen : forceGenerators_)
  {
    forces_ += gen->GenerateForce();
  }
}

void PhysicsComponent::AddForceGenerator(ForceGenerator* forceGenerator)
{
  forceGenerator->body_ = this;
  forceGenerators_.push_back(forceGenerator);
}

void PhysicsComponent::AddVelocity(const glm::vec2& velToAdd)
{
  velocity_ += velToAdd;
}

float PhysicsComponent::GetRotationalVelocity() const
{
  return rotationalVelocity_;
}

glm::vec2 PointForceGenerator::GenerateForce()
{
  Transform& transform = body_->GetParent()->GetTransform();

  //pointToPull_ = Engine::Instance()->GetMousePosition();

  return pointToPull_ - transform.GetPosition();
}
