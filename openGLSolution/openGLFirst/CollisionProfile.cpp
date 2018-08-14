#include "stdafx.h"
#include "CollisionProfile.h"
#include "CollisionComponent.h"


CollisionProfile::CollisionProfile()
{
}


CollisionProfile::~CollisionProfile()
{
}

CollisionComponent* CollisionProfile::GetCollisionComponent() const
{
  return collisionComponent_;
}

void CollisionProfile::SetCollisionComponent(CollisionComponent* thisCollider)
{
  collisionComponent_ = thisCollider;
}

