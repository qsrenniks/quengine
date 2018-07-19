#include "stdafx.h"
#include "PhysicsComponent.h"
#include "IGameObject.h"
#include "Transform.h"
#include "CollisionOccurence.h"
#include "RigidBodyGameObject.h"

//PhysicsConstants
glm::vec2 PhysicsComponent::Gravity = glm::vec2(0.0f, -1.0f);

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

//void PhysicsComponent::Draw()
//{
//
//}

void PhysicsComponent::Update(float dt)
{
  if (simulatePhysics_ == false) return;
  //maybe this instead returns a direction that velocity should be clamped to 
  //if (GetParent()->PreventPhysics()) return; 

  Transform& transformComp = GetParent()->GetTransform();

  glm::vec2 translation{0};

  //if (physicalProperties_.mass_ == 0.0f)
  //{
  //  acceleration_ = (1 / physicalProperties_.mass_) * velocity_;
  //}

  velocity_ = velocity_ + (acceleration_ * dt);

  translation = (velocity_ * dt) + transformComp.GetPosition();

  transformComp.SetPosition(glm::vec2(translation));

  //velocity_ *= physicalProperties_.velocityDecay_;

  float rotation = transformComp.GetRotation();

  rotation += GetRotationalVelocity() * dt;

  transformComp.SetRotation(rotation);
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

void PhysicsComponent::SetPhysicalProperties(float mass, float friction, float bounce)
{
  physicalProperties_.mass_ = mass;
  physicalProperties_.friction_ = friction;
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

void PhysicsComponent::SetFriction(float friction)
{
  physicalProperties_.friction_;
}

void PhysicsComponent::SetBounce(float bounce)
{
  physicalProperties_.bounce_ = bounce;
}

void PhysicsComponent::SetVelocityDecay(float velocityDecay)
{
  physicalProperties_.velocityDecay_ = velocityDecay;
}

//static
void PhysicsComponent::RespondToPhysicalCollision(CollisionOccurence& occurence)
{
  //do physics math here.

  //auto mtvTranslation = [&](RigidBodyGameObject)
  //{

  //};

  auto mtvTranslation = [=](RigidBodyGameObject* object, const glm::vec2& mtv)
  {
    Transform& objectTransform = object->GetTransform();

    glm::vec2 objectOldPosition = objectTransform.GetPosition();

    objectOldPosition += mtv;

    objectTransform.SetPosition(objectOldPosition);
  };

  //glm::vec2 mtv = occurence.mtv_ / 2.0f;
  //mtvTranslation(occurence.objectA_, -mtv);
  //mtvTranslation(occurence.objectB_, mtv);

  PhysicsComponent *objectAPhysics = occurence.objectA_->GetPhysicsComponent();
  PhysicsComponent *objectBPhysics = occurence.objectB_->GetPhysicsComponent();

  //mtvTranslation(occurence.objectB_, occurence.mtv_);

  if (objectAPhysics->GetSimulatePhysics() == true && objectBPhysics->GetSimulatePhysics() == true)
  {
    mtvTranslation(occurence.objectA_, occurence.mtv_AFROMB);
    mtvTranslation(occurence.objectB_, occurence.mtv_BFROMA);
  }
  else if (objectBPhysics->GetSimulatePhysics() == true && objectAPhysics->GetSimulatePhysics() == false)
  {
    mtvTranslation(occurence.objectB_, occurence.mtv_);
  }
  else if (objectAPhysics->GetSimulatePhysics() == true && objectBPhysics->GetSimulatePhysics() == false)
  {
    mtvTranslation(occurence.objectA_, -occurence.mtv_);
  }

  
  glm::vec2 AVelocityFinal;
  glm::vec2 BVelocityFinal;

  AVelocityFinal = objectAPhysics->CalculateEllasticCollision(objectBPhysics, occurence.mtv_AFROMB);
  BVelocityFinal = objectBPhysics->CalculateEllasticCollision(objectAPhysics, occurence.mtv_BFROMA);

  objectAPhysics->SetVelocity(AVelocityFinal);
  objectBPhysics->SetVelocity(BVelocityFinal);
}

//this calculates the new velocity of the object on impact.
glm::vec2 PhysicsComponent::CalculateEllasticCollision(const PhysicsComponent* physicsComponent, const glm::vec2& mtv)
{

  glm::vec2 normalizedMTV;
  if (mtv.x == 0.0f && mtv.y == 0.0f)
  {
    normalizedMTV = glm::vec2(0.0f, 0.0f);
  }
  else
  {
    normalizedMTV = glm::normalize(mtv);
  }

  glm::vec2 normalizedVelocity;
  if (velocity_.x == 0.0f && velocity_.y == 0.0f)
  {
    normalizedVelocity = glm::vec2(0.0f, 0.0f);
  }
  else
  {
    normalizedVelocity = glm::normalize(velocity_);
  }

  glm::vec2 s = normalizedMTV * glm::length(velocity_);
  s *= glm::abs(glm::dot(normalizedVelocity, normalizedMTV));

  glm::vec2 thisVelocityFinal = ((velocity_ + s) * physicalProperties_.friction_) + (s * physicalProperties_.bounce_);

  return thisVelocityFinal;
}

float PhysicsComponent::GetRotationalVelocity() const
{
  return rotationalVelocity_;
}
