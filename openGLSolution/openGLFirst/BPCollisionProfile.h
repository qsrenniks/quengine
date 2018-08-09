#pragma once
class BPCollisionProfile
{
public:
  BPCollisionProfile();
  ~BPCollisionProfile();

  //re-calculates the objects aabb give the farthest away vertex.
  void UpdateAABB();

protected:



private:

};

