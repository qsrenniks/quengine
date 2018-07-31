#include "stdafx.h"
#include "PhysicsComponent.h"
#include "IGameObject.h"
#include "Transform.h"
#include "CollisionOccurence.h"
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/vector_angle.hpp>
#include "RigidBodyGameObject.h"
#include <algorithm>
#include "Engine.h"

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

  Transform& transform = GetParent()->GetTransform();

  glm::vec2 newPos = transform.GetPosition() + velocity_ * dt;

  transform.SetPosition(newPos);

  velocity_ = velocity_ * glm::pow(physicalProperties_.velocityDecay_, dt) + acceleration_ * dt;

  acceleration_ = physicalProperties_.GetInverseMass() * forces_;

  ResetForces();
}

void PhysicsComponent::Draw()
{
  //do nothing. nothing needs to be drawn here.
}

void PhysicsComponent::SetAcceleration(const glm::vec2& newAcceleration)
{
  //acceleration_ = newAcceleration;
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

const glm::vec2& PhysicsComponent::GetVelocity() const
{
  return velocity_;
}

void PhysicsComponent::SetRotationalVelocity(float val)
{
  rotationalVelocity_ = val;
}

const PhysicalProperties& PhysicsComponent::GetPhysicsProperties() const
{
  return physicalProperties_;
}

void PhysicsComponent::SetPhysicalProperties(float mass, float bounce)
{
  physicalProperties_.mass_ = mass;
  physicalProperties_.bounce_ = bounce;
}

void PhysicsComponent::SetPhysicalProperties(const PhysicalProperties& physicalProperties)
{
  physicalProperties_ = physicalProperties;
}

void PhysicsComponent::SetMass(float mass)
{
  physicalProperties_.mass_ = mass;
}

void PhysicsComponent::SetBounce(float bounce)
{
  physicalProperties_.bounce_ = bounce;
}

void PhysicsComponent::SetVelocityDecay(float x )
{
  physicalProperties_.velocityDecay_ = x;
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
  velocity_ = velocity_ + physicalProperties_.GetInverseMass()*impulse;
}

const glm::vec2& PhysicsComponent::GetCurrentForce()
{
  return forces_;
}

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

float PhysicalProperties::GetInverseMass() const
{
  if (mass_ == 0)
  {
    return 0;
  }
  else
  {
    return 1 / mass_;
  }
}

glm::vec2 PointForceGenerator::GenerateForce()
{
  Transform& transform = body_->GetParent()->GetTransform();

  //pointToPull_ = Engine::Instance()->GetMousePosition();

  return pointToPull_ - transform.GetPosition();
}
