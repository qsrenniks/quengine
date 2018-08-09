#pragma once

#include "NPCollisionProfile.h"
#include <vector>
#include <glm/detail/type_vec.hpp>

struct CollisionOccurence;
class Mesh;

enum class CollisionStatus : int;

//
// most rudementary square collision profile that uses the mesh on the sprite component of the object its created with.
// this currenlty should be renamed to polygonal collision profile since it will adapt to the shape of the mesh on the sprite component.
// however it currenlty assumes the mesh is a square and only checks 4 verts. This should later be changed to account for meshes of all verts and shapes.
//
class PolygonalCollisionProfile : public NPCollisionProfile
{
public:
  PolygonalCollisionProfile();

  virtual void IsProfileCollidingWith(NPCollisionProfile* otherProfile, CollisionOccurence& collOcc) const override;

  CollisionStatus PerformAxisProjection(const std::vector<glm::vec2>& axisA, Mesh &meshA, Mesh &meshB, float &overlap, glm::vec2 &smallestAxis) const;

private:

};