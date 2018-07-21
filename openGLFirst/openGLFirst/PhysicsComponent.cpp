#include "stdafx.h"
#include "PhysicsComponent.h"
#include "IGameObject.h"
#include "Transform.h"
#include "CollisionOccurence.h"
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/vector_angle.hpp>
#include "RigidBodyGameObject.h"
#include <algorithm>

//PhysicsConstants
glm::vec2 PhysicsComponent::Gravity = glm::vec2(0.0f, -300.);

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

  Transform& transformComp = GetParent()->GetTransform();

  glm::vec2 translation{0};

  velocity_ = velocity_ + (acceleration_ * dt);

  translation = (velocity_ * dt) + transformComp.GetPosition();

  transformComp.SetPosition(glm::vec2(translation));

  float rotation = transformComp.GetRotation();

  rotation += GetRotationalVelocity() * dt;

  transformComp.SetRotation(rotation);

  velocity_ *= physicalProperties_.velocityDecay_;
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

void PhysicsComponent::SetVelocityDecay(float x, float y )
{
  physicalProperties_.velocityDecay_.x = x;
  physicalProperties_.velocityDecay_.y = y;
}

void PhysicsComponent::RespondToPhysicalCollision(CollisionOccurence& occurence)
{
  PhysicsComponent *objectAPhysics = occurence.objectA_->GetPhysicsComponent();
  PhysicsComponent *objectBPhysics = occurence.objectB_->GetPhysicsComponent();

  glm::vec2 AVelocityFinal = objectAPhysics->GetVelocity();
  glm::vec2 BVelocityFinal = objectBPhysics->GetVelocity();

  glm::vec2 rv = objectBPhysics->GetVelocity() - objectAPhysics->GetVelocity();

  glm::vec2 normal = glm::normalize(occurence.mtv_);
  if (glm::isnan(normal).x == 1.0f)
  {
    normal = glm::vec2(0.0f, 0.0f);
  }

  float velAlongNormal = glm::dot(rv, normal);

  if (velAlongNormal > 0)
  {
    return;
  }

  float e = std::min(objectAPhysics->GetPhysicsProperties().bounce_, objectBPhysics->GetPhysicsProperties().bounce_);

  //bounce velocity mag
  float bounceVeloMag = -(1 + e) * velAlongNormal;
  bounceVeloMag /= (objectAPhysics->GetPhysicsProperties().GetInverseMass()) + (objectBPhysics->GetPhysicsProperties().GetInverseMass());

  glm::vec2 impulse = bounceVeloMag * normal;

  AVelocityFinal -= (objectAPhysics->GetPhysicsProperties().GetInverseMass()) * impulse;
  BVelocityFinal += (objectBPhysics->GetPhysicsProperties().GetInverseMass()) * impulse;

  const static float percent = 1.0f;
  glm::vec2 correction = (glm::length(occurence.mtv_) / (objectAPhysics->GetPhysicsProperties().GetInverseMass() + objectBPhysics->GetPhysicsProperties().GetInverseMass())) * percent * normal;

  glm::vec2 positionA = objectAPhysics->GetParent()->GetTransform().GetPosition();
  glm::vec2 positionB = objectBPhysics->GetParent()->GetTransform().GetPosition();

  positionA -= objectAPhysics->GetPhysicsProperties().GetInverseMass() * correction;
  positionB += objectBPhysics->GetPhysicsProperties().GetInverseMass() * correction;

  objectAPhysics->GetParent()->GetTransform().SetPosition(positionA);
  objectAPhysics->SetVelocity(AVelocityFinal);

  objectBPhysics->GetParent()->GetTransform().SetPosition(positionB);
  objectBPhysics->SetVelocity(BVelocityFinal);
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
