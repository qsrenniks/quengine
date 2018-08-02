#include "stdafx.h"
#include "CollisionOccurence.h"
#include "PhysicsComponent.h"
#include "Transform.h"
#include "CollisionComponent.h"
#include "Engine.h"
#include "RigidBodyComponent.h"

bool CollisionOccurence::operator==(const CollisionOccurence& otherCollision) const
{
  if (objectA_ == otherCollision.objectA_ && objectB_ == otherCollision.objectB_
      || objectA_ == otherCollision.objectB_ && objectB_ == otherCollision.objectA_ )
  {
    return true;
  }
  else return false;
}

void CollisionOccurence::Resolve()
{
  float dt = Engine::Instance()->GetDeltaTime();

  float invMassesSum = objectA_->GetPhysicsComponent()->GetInverseMass() + objectB_->GetPhysicsComponent()->GetInverseMass();
  if (invMassesSum <= 0.0f)
  {
    return;
  }

  ResolveVelocities(dt);
  ResolveInterpenetration(dt);
}

void CollisionOccurence::ResolveVelocities(float dt)
{
  PhysicsComponent* physicsA = objectA_->GetPhysicsComponent();
  PhysicsComponent* physicsB = objectB_->GetPhysicsComponent();

  float seperatingVelocity = 0;

  glm::vec2 relativeVelocity = physicsA->GetVelocity() - physicsB->GetVelocity();

  seperatingVelocity = glm::dot(relativeVelocity, collisionNormal_);

  if (seperatingVelocity > 0)
  {
    return;
  }
  
  float newSepVelocity = -seperatingVelocity * restitution_;

  glm::vec2 accCausedVelocity = physicsA->GetAcceleration() - physicsB->GetAcceleration();

  float accCausedSepVelocity = glm::dot(accCausedVelocity, collisionNormal_) * dt;
   
  if (accCausedSepVelocity < 0)
  {
    newSepVelocity += restitution_ * accCausedSepVelocity;

    if (newSepVelocity < 0.0f)
    {
      newSepVelocity = 0.0f;
    }
  }

  float deltaVelocity = newSepVelocity - seperatingVelocity;

  float totalInverseMass = physicsA->GetInverseMass() + physicsB->GetInverseMass();

  if (totalInverseMass <= 0)
  {
    return;
  }

  float impulse = deltaVelocity / totalInverseMass;

  glm::vec2 impulsePerIMass = collisionNormal_ * impulse;

  physicsA->SetVelocity(physicsA->GetVelocity() + impulsePerIMass * physicsA->GetInverseMass());
  physicsB->SetVelocity(physicsB->GetVelocity() + impulsePerIMass * -physicsB->GetInverseMass());

  /* glm::vec2 relativeVelocity = physicsB->GetVelocity() - physicsA->GetVelocity();

  float impulseMagnitudeAlongNormal = glm::dot(relativeVelocity, collisionNormal_);

  if (impulseMagnitudeAlongNormal > 0)
  {
    return;
  }

  float impulseScalar = -(1+restitution_) * impulseMagnitudeAlongNormal;*/
  
  //float velocityFromAcc = glm::dot(physicsA->GetAccelerationLastFrame(), collisionNormal_);
  //if (physicsB->GetInverseMass() != 0.0f)
  //{
  //  velocityFromAcc -= glm::dot(physicsB->GetAccelerationLastFrame(), collisionNormal_);
  //}
  //float deltaVelocity = -relativeVelocity.x - restitution_ * (relativeVelocity.x - velocityFromAcc);
  //
 /* float inverseMassSum = physicsA->GetInverseMass() + physicsB->GetInverseMass();
  impulseScalar /= inverseMassSum;

  glm::vec2 impulse = impulseScalar * collisionNormal_;

  float aInvMass = physicsA->GetInverseMass();
  float bInvMass = physicsB->GetInverseMass();

  physicsA->AddVelocity(-(aInvMass * impulse));
  physicsB->AddVelocity(bInvMass* impulse);*/
}

void CollisionOccurence::ResolveInterpenetration(float dt)
{
  PhysicsComponent* physicsA = objectA_->GetPhysicsComponent();
  PhysicsComponent* physicsB = objectB_->GetPhysicsComponent();

  Transform& transformA = objectA_->GetParent()->GetTransform();
  Transform& transformB = objectB_->GetParent()->GetTransform();

  if (penetration_ <= 0.0f)
  {
    return;
  }

  float totalInverseMass = physicsA->GetInverseMass() + physicsB->GetInverseMass();

  //if (totalInverseMass <= 0.0f)
  //{
  //  return;
  //}

  glm::vec2 movePerIMass = collisionNormal_ * (penetration_ / totalInverseMass);

  glm::vec2 movementA = movePerIMass * physicsA->GetInverseMass();
  glm::vec2 movementB = movePerIMass * -physicsB->GetInverseMass();

  transformA.SetPosition(transformA.GetPosition() + movementA);
  transformB.SetPosition(transformB.GetPosition() + movementB);

  //const static float percentage = 0.2f;
  //glm::vec2 correction = penetration_ / (physicsA->GetInverseMass() + physicsB->GetInverseMass()) * percentage * collisionNormal_;

  //transformA.SetPosition(transformA.GetPosition() - physicsA->GetInverseMass() * correction);
  //transformB.SetPosition(transformB.GetPosition() + physicsB->GetInverseMass() * correction);
}
