#include "stdafx.h"
#include "CollisionOccurence.h"
#include "PhysicsComponent.h"
#include "Transform.h"
#include "CollisionComponent.h"

bool CollisionOccurence::operator==(CollisionOccurence otherCollision) const
{
  if (objectA_ == otherCollision.objectA_ && objectB_ == otherCollision.objectB_)
  {
    return true;
  }
  else return false;
}

void CollisionOccurence::ConstructNonCollisionOccurence(CollisionComponent* objectA, CollisionComponent* objectB, CollisionStatus collisionStatus)
{
  objectA_ = objectA;
  objectB_ = objectB;

  mtv_ = glm::vec2(0.0f, 0.0f);

  collisionStatus_ = collisionStatus;
}

CollisionOccurence CollisionOccurence::operator-()
{
  CollisionOccurence copy = *this;

  copy.mtv_ *= -1.0f;
  copy.halfMtv_ *= -1.0f;

  return copy;
}
