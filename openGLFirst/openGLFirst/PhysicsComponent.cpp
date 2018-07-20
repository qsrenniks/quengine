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


void PhysicsComponent::Update(float dt)
{
  if (simulatePhysics_ == false) return;

  //reset average calculation
  ResetAverages();

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
  auto mtvTranslation = [=](RigidBodyGameObject* object, const glm::vec2& mtv)
  {
    Transform& objectTransform = object->GetTransform();

    glm::vec2 objectOldPosition = objectTransform.GetPosition();

    objectOldPosition += mtv;

    objectTransform.SetPosition(objectOldPosition);
  };

  PhysicsComponent *objectAPhysics = occurence.objectA_->GetPhysicsComponent();
  PhysicsComponent *objectBPhysics = occurence.objectB_->GetPhysicsComponent();

  //if (objectAPhysics->GetSimulatePhysics() == true && objectBPhysics->GetSimulatePhysics() == true)
  //{
  //  mtvTranslation(occurence.objectA_, occurence.mtv_AFROMB);
  //  mtvTranslation(occurence.objectB_, occurence.mtv_BFROMA);

  //  //occurence.objectA_
  //}
  //else if (objectBPhysics->GetSimulatePhysics() == true && objectAPhysics->GetSimulatePhysics() == false)
  //{
  //  mtvTranslation(occurence.objectB_, occurence.mtv_);
  //}
  //else if (objectAPhysics->GetSimulatePhysics() == true && objectBPhysics->GetSimulatePhysics() == false)
  //{
  //  mtvTranslation(occurence.objectA_, -occurence.mtv_);
  //}
  //
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

  float j = -(1 + e) * velAlongNormal;
  j /= (objectAPhysics->GetPhysicsProperties().GetInverseMass()) + (objectBPhysics->GetPhysicsProperties().GetInverseMass());

  glm::vec2 impulse = j * normal;

  //AVelocityFinal = objectAPhysics->CalculateBounceVelocities(objectBPhysics, occurence.mtv_AFROMB);
  //BVelocityFinal = objectBPhysics->CalculateBounceVelocities(objectAPhysics, occurence.mtv_BFROMA);
  AVelocityFinal -= (objectAPhysics->GetPhysicsProperties().GetInverseMass()) * impulse;
  BVelocityFinal += (objectBPhysics->GetPhysicsProperties().GetInverseMass()) * impulse;

  //float mass_sum = objectAPhysics->GetPhysicsProperties().mass_ + objectBPhysics->GetPhysicsProperties().mass_;

  //float ratio = objectAPhysics->GetPhysicsProperties().mass_ / mass_sum;
  //AVelocityFinal -= ratio * impulse;
  //
  //ratio = objectBPhysics->GetPhysicsProperties().mass_ / mass_sum;
  //BVelocityFinal += ratio * impulse;

  //positional correction here
  const static float percent = 1.0f;
  //const static float slop = 0.01f;

  glm::vec2 correction = (glm::length(occurence.mtv_) / (objectAPhysics->GetPhysicsProperties().GetInverseMass() + objectBPhysics->GetPhysicsProperties().GetInverseMass())) * percent * normal;

  glm::vec2 positionA = objectAPhysics->GetParent()->GetTransform().GetPosition();
  glm::vec2 positionB = objectBPhysics->GetParent()->GetTransform().GetPosition();

  positionA -= objectAPhysics->GetPhysicsProperties().GetInverseMass() * correction;
  positionB += objectBPhysics->GetPhysicsProperties().GetInverseMass() * correction;

  objectAPhysics->GetParent()->GetTransform().SetPosition(positionA);
  objectBPhysics->GetParent()->GetTransform().SetPosition(positionB);

  objectAPhysics->SetVelocity(AVelocityFinal);
  objectBPhysics->SetVelocity(BVelocityFinal);

  //glm::vec2 aPushVelo;
  //glm::vec2 bPushVelo;

  //objectAPhysics->CalculateTwoDEllasticCollision(objectBPhysics, aPushVelo, bPushVelo);

  //objectAPhysics->SetVelocity(aPushVelo);
  //objectBPhysics->SetVelocity(bPushVelo);
  //2dEllasticCollision
  //objectAPhysics->AddAverageVelocity(AVelocityFinal);
  //objectBPhysics->AddAverageVelocity(BVelocityFinal);
}

//this calculates the new velocity of the object on impact.
glm::vec2 PhysicsComponent::CalculateBounceVelocities(const PhysicsComponent* physicsComponent, const glm::vec2& mtv)
{
  glm::vec2 normalizedMTV;
  if (glm::epsilonEqual(mtv.x, 0.0f, 0.00004f) && glm::epsilonEqual(mtv.y, 0.0f, 0.00004f))
  {
    normalizedMTV = glm::vec2(0.0f, 0.0f);
  }
  else
  {
    normalizedMTV = glm::normalize(mtv);
  }

  glm::vec2 normalizedVelocity;
  if (glm::epsilonEqual(velocity_.x, 0.0f, 0.004f) && glm::epsilonEqual(velocity_.y, 0.0f, 0.004f))
  {
    normalizedVelocity = glm::vec2(0.0f, 0.0f);
  }
  else
  {
    normalizedVelocity = glm::normalize(velocity_);
  }

  glm::vec2 s = normalizedMTV * glm::length(velocity_);

  float dotP = glm::dot(normalizedVelocity, normalizedMTV);

  if (dotP <= 0)
  {
    dotP = glm::abs(dotP);
  }
  else if (dotP > 0) //if the velocity is in the direction of mtv then dont calculate a second bounce.
  {
    dotP = 0;
  }

  s *= dotP;

  glm::vec2 thisVelocityFinal = ((velocity_ + s) * physicalProperties_.friction_) + (s * physicalProperties_.bounce_);
  //glm::vec2 thisVelocityFinal;

  //thisVelocityFinal = glm::reflect(velocity_, glm::normalize(mtv));

  return thisVelocityFinal;
}

void PhysicsComponent::CalculateTwoDEllasticCollision(const PhysicsComponent* physicsComponent, glm::vec2& veloOneFinal, glm::vec2& veloTwoFinal)
{
  float massOne = physicalProperties_.mass_;
  float massTwo = physicsComponent->GetPhysicsProperties().mass_;

  glm::vec2 initVeloOne = velocity_;
  glm::vec2 initVeloTwo = physicsComponent->GetVelocity();

  glm::vec2 OnePosition = GetParent()->GetTransform().GetPosition();
  glm::vec2 TwoPosition = physicsComponent->GetParent()->GetTransform().GetPosition();

  float theta = glm::orientedAngle(initVeloOne, initVeloTwo);
  
  float finalVONEA = (2 * massTwo) / (massOne + massTwo);
  float finalVONEB = (glm::dot(initVeloOne - initVeloTwo, OnePosition - TwoPosition)) / (glm::length(OnePosition - TwoPosition));
  glm::vec2 finalVONEC = (OnePosition - TwoPosition);

  veloOneFinal = initVeloOne - (finalVONEA * finalVONEB * finalVONEC);

  float finalVTWOA = (2 * massOne) / (massOne + massTwo);
  float finalVTWOB = (glm::dot(initVeloTwo-initVeloOne, TwoPosition - OnePosition)) / glm::length(TwoPosition - OnePosition);
  glm::vec2 finalVTWOC = (TwoPosition - OnePosition);

  veloTwoFinal = initVeloTwo - (finalVTWOA * finalVTWOB * finalVTWOC);
}

void PhysicsComponent::AddAverageVelocity(const glm::vec2& vector)
{
  numberOfAverages_++;
  velocity_ += vector;
  velocity_ /= numberOfAverages_; 
}

void PhysicsComponent::ResetAverages()
{
  numberOfAverages_ = 1;
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
