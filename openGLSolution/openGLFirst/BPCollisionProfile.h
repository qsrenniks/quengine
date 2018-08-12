#pragma once
#include "CollisionProfile.h"

class BPCollisionProfile : public CollisionProfile
{
public:
  BPCollisionProfile();
  ~BPCollisionProfile();

  //re-calculates the objects aabb give the farthest away vertex.
  void UpdateAABB();

protected:



private:

};

