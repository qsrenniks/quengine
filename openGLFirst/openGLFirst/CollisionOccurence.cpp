#include "stdafx.h"
#include "CollisionOccurence.h"
#include "PhysicsComponent.h"
#include "Transform.h"
#include "CollisionComponent.h"

bool CollisionOccurence::operator==(const CollisionOccurence& otherCollision) const
{
  if (objectA_ == otherCollision.objectA_ && objectB_ == otherCollision.objectB_)
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

bool CollisionOccurence::IsValid()
{
  return isValid_;
}

void CollisionOccurence::SetValid(bool validity)
{
  isValid_ = validity;
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
