#include "stdafx.h"
#include "CollisionOccurence.h"
#include "PhysicsComponent.h"
#include "RigidBodyGameObject.h"
#include "Transform.h"
#include "CollisionComponent.h"
#include "Engine.h"

bool CollisionOccurence::operator==(const CollisionOccurence& otherCollision) const
{
  if (objectA_ == otherCollision.objectA_ && objectB_ == otherCollision.objectB_
      || objectA_ == otherCollision.objectB_ && objectB_ == otherCollision.objectA_ )
  {
    return true;
  }
  else return false;
}

void CollisionOccurence::ConstructNonCollisionOccurence(RigidBodyGameObject* objectA, RigidBodyGameObject* objectB, CollisionStatus collisionStatus)
{
  objectA_ = objectA;
  objectB_ = objectB;

  mtv_ = glm::vec2(0.0f, 0.0f);

  collisionStatus_ = collisionStatus;
}

void CollisionOccurence::Resolve()
{
  float dt = Engine::Instance()->GetDeltaTime();

  ResolveVelocities(dt);
  ResolveInterpenetration(dt);
}

bool CollisionOccurence::IsValid()
{
  return isValid_;
}

void CollisionOccurence::SetValid(bool validity)
{
  isValid_ = validity;
}

void CollisionOccurence::ResolveVelocities(float dt)
{
  //for object A
  //calculate seperating velocities
  glm::vec2 relativeVelocity = objectA_->GetPhysicsComponent()->GetVelocity();
  if (objectB_->GetPhysicsComponent()->GetPhysicsProperties().GetInverseMass() != 0.0f)
  {
    relativeVelocity -= objectB_->GetPhysicsComponent()->GetVelocity();
  }

  //recommend putting normal contact somwhere else.
  float seperatingVelocity = glm::dot(relativeVelocity, collisionNormal_);
  
  if (seperatingVelocity > 0)
  {
    //if they are already seperating dont do anything more.
    return;
  }

  float newSepVelo = -seperatingVelocity * restitution_;

  //check the velocity buildup due to acceleration only
  glm::vec2 accelerationCausedVelocity = objectA_->GetPhysicsComponent()->GetAcceleration();
  if (objectB_->GetPhysicsComponent()->GetPhysicsProperties().GetInverseMass() != 0.0f)
  {
    accelerationCausedVelocity -= objectB_->GetPhysicsComponent()->GetAcceleration();
  }

  float accCausedSepVelocity = glm::dot(accelerationCausedVelocity, collisionNormal_) * dt;

  //if weve got a closing velocity due to acceleration buildup remove it from the new seperating velocity
  if (accCausedSepVelocity < 0)
  {
    newSepVelo += restitution_ * accCausedSepVelocity;

    if (newSepVelo < 0)
    {
      newSepVelo = 0;
    }
  }
  
  float deltaVelocity = newSepVelo - seperatingVelocity;

  float totalInverseMass = objectA_->GetPhysicsComponent()->GetPhysicsProperties().GetInverseMass();
  if (objectB_->GetPhysicsComponent()->GetPhysicsProperties().GetInverseMass() != 0.0f)
  {
    totalInverseMass += objectB_->GetPhysicsComponent()->GetPhysicsProperties().GetInverseMass();
  }

  //if all particles have infinite mass then no effects are applied
  if (totalInverseMass <= 0)
  {
    return;
  }

  float impulse = deltaVelocity / totalInverseMass;

  glm::vec2 impulsePerIMass = collisionNormal_ * impulse;

  glm::vec2 otherVelo = objectB_->GetPhysicsComponent()->GetVelocity();

  objectA_->GetPhysicsComponent()->SetVelocity(otherVelo + impulsePerIMass * objectA_->GetPhysicsComponent()->GetPhysicsProperties().GetInverseMass());
  if (objectB_->GetPhysicsComponent()->GetPhysicsProperties().GetInverseMass() != 0.0f)
  {
    objectB_->GetPhysicsComponent()->SetVelocity(objectA_->GetPhysicsComponent()->GetVelocity() + impulsePerIMass * -objectB_->GetPhysicsComponent()->GetPhysicsProperties().GetInverseMass());
  }
}

void CollisionOccurence::ResolveInterpenetration(float dt)
{
  //for object A
  if (penetration_ <= 0.0f)
  {
    return;
  }

  float totalInverseMass = objectA_->GetPhysicsComponent()->GetPhysicsProperties().GetInverseMass();
  if (objectB_->GetPhysicsComponent()->GetPhysicsProperties().GetInverseMass() != 0.0f)
  {
    totalInverseMass += objectB_->GetPhysicsComponent()->GetPhysicsProperties().GetInverseMass();
  }

  //if all particles have infinite mass then no effects are applied
  if (totalInverseMass <= 0)
  {
    return;
  }

  glm::vec2 movePerIMass = collisionNormal_ * (penetration_ / totalInverseMass);

  glm::vec2 newPositionA;
  glm::vec2 newPositionB;

  newPositionA = (movePerIMass * objectA_->GetPhysicsComponent()->GetPhysicsProperties().GetInverseMass());
  if (objectB_->GetPhysicsComponent()->GetPhysicsProperties().GetInverseMass() != 0.0f)
  {
    newPositionB = (movePerIMass * -objectB_->GetPhysicsComponent()->GetPhysicsProperties().GetInverseMass());
  }
  else
  {
    newPositionB.x = 0.0f;
    newPositionB.y = 0.0f;
  }

  objectA_->GetTransform().SetPosition(objectA_->GetTransform().GetPosition() + newPositionA);
  objectB_->GetTransform().SetPosition(objectB_->GetTransform().GetPosition() + newPositionB);
}

//CollisionOccurence CollisionOccurence::operator-()
//{
//  CollisionOccurence copy = *this;
//
//  copy.mtv_ *= -1.0f;
//  copy.halfMtv_ *= -1.0f;
//
//  return copy;
//}
