#include "stdafx.h"
#include "NPCollisionProfile.h"

NPCollisionProfile::NPCollisionProfile()
{
}

CollisionComponent* NPCollisionProfile::GetCollisionComponent()
{
  return collisionComponent_;
}

void NPCollisionProfile::SetCollisionComponent(CollisionComponent* thisCollider)
{
  collisionComponent_ = thisCollider;
}

