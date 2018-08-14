#pragma once
#include "CollisionProfile.h"
#include "Mesh.h"
#include <vector>

class CollisionComponent;
struct CollisionOccurence;

//
// Base class for collision profile. Derive from this to create a new profile with custom collision detection methods
//
// NP Stands for Narrow Phase
//
class NPCollisionProfile : public CollisionProfile
{
public: //Types

  Mesh npMeshProfile_;

public:

  NPCollisionProfile(std::initializer_list<Vertex> vertexList, std::initializer_list<unsigned int> indices);

  virtual CollisionStatus IsProfileCollidingWith(CollisionProfile* otherProfile) const override;

  const Mesh& GetMesh() const;

  void SetFillerOccurence(CollisionOccurence& collOcc);

protected:

  CollisionOccurence* fillerOccurence_ = nullptr;
};
