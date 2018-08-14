#pragma once
#include "CollisionProfile.h"

class BPCollisionProfile : public CollisionProfile
{
public:
  BPCollisionProfile(const glm::vec2& extent);
  ~BPCollisionProfile();


  //re-calculates the objects aabb give the farthest away vertex.
  void UpdateAABB(const glm::vec2& newLocation, const glm::vec2& newScale);

  virtual CollisionStatus IsProfileCollidingWith(CollisionProfile* otherProfile) const override;

  const glm::vec2& GetAABBExtent() const;
  const glm::vec2& GetAABBLocation() const;

  void SetAABBExtent(const glm::vec2& extent);

protected:

  glm::vec2 offsetExtent_;
  glm::vec2 extent_;
  glm::vec2 location_;

private:

};

