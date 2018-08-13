#include "stdafx.h"
#include "BPCollisionProfile.h"
#include "CollisionOccurence.h"
#include "glm/gtc/matrix_transform.hpp"

BPCollisionProfile::BPCollisionProfile(const glm::vec2& extent)
  : extent_(extent)
{
}

BPCollisionProfile::~BPCollisionProfile()
{

}

void BPCollisionProfile::UpdateAABB(const glm::vec2& newLocation)
{
  location_ = newLocation;
}

CollisionStatus BPCollisionProfile::IsProfileCollidingWith(CollisionProfile* otherProfile) const
{
  BPCollisionProfile* bpOtherProfile = dynamic_cast<BPCollisionProfile*>(otherProfile);

  if (bpOtherProfile == nullptr)
  {
    return CollisionStatus::INVALID;
  }

  glm::vec2 bExtent = bpOtherProfile->GetAABBExtent();
  glm::vec2 bLocation = bpOtherProfile->GetAABBLocation();

  //#Note AABB Collision Check
  if (location_.x < bLocation.x + bExtent.x && 
      location_.x + extent_.x > bLocation.x &&
      location_.y < bLocation.y + bExtent.y &&
      extent_.y + location_.y > bLocation.y)
  {
    //they are colliding
    return CollisionStatus::COLLIDING;
  }

  return CollisionStatus::NOT_COLLIDING;
}

const glm::vec2& BPCollisionProfile::GetAABBExtent() const
{
  return extent_;
}

const glm::vec2& BPCollisionProfile::GetAABBLocation() const
{
  return location_;
}

void BPCollisionProfile::SetAABBExtent(const glm::vec2& extent)
{
  extent_ = extent;
}
