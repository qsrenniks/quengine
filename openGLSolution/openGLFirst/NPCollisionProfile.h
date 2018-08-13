#pragma once
#include "CollisionProfile.h"
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

  using VertexList = std::vector<glm::vec2>;
  using EdgeList = std::vector<glm::vec2>;

public:

  NPCollisionProfile(/*std::initializer_list<glm::vec2> vertexList*/);

  virtual CollisionStatus IsProfileCollidingWith(CollisionProfile* otherProfile) const override;

  const VertexList& GetVertexList() const;

  void SetFillerOccurence(CollisionOccurence& collOcc);

protected:

  CollisionOccurence* fillerOccurence_;

  VertexList vertices_;
  EdgeList edgeNormals_;

};
