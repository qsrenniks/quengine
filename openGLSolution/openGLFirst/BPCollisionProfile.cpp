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

  glm::vec2 aExtent = extent_;
  aExtent *= 2.0f;
  glm::vec2 bExtent = bpOtherProfile->GetAABBExtent();
  bExtent *= 2.0f;

  glm::vec2 aLocation = location_;
  glm::vec2 bLocation = bpOtherProfile->GetAABBLocation();
  
  bool isColliding = (std::abs(aLocation.x - bLocation.x) * 2 < (aExtent.x + bExtent.x)) && (std::abs(aLocation.y - bLocation.y) * 2 < (aExtent.y + bExtent.y));

  //#Note AABB Collision Check
  if(isColliding)
  {
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
