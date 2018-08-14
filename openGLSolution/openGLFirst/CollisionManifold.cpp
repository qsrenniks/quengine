#include "stdafx.h"
#include "CollisionManifold.h"
#include "CollisionOccurence.h"
#include "Vertex.h"

CollisionManifold::CollisionManifold(float min /*= 0.0f*/, float max /*= 0.0f*/)
  : min_(min)
  , max_(max)
{
  
}

CollisionManifold::~CollisionManifold()
{
}

void CollisionManifold::ProjectVerticesOntoEdge(const glm::vec3& first, const glm::vec3& second, const glm::vec2& edge)
{
  //project the vertexes onto the edge
  //edge is always normalized so just project
  float a = glm::dot(first, glm::vec3(edge, 0.0f));
  float b = glm::dot(second, glm::vec3(edge, 0.0f));

  if (a < b)
  {
    min_ = a;
    max_ = b;
  }
  else
  {
    min_ = b;
    max_ = a;
  }
}

CollisionStatus CollisionManifold::IsOverlapping(const CollisionManifold& otherManifold)
{
  //if they are overlapping either one of the min and max will be inside the other.
  //
  // a-----b----A--------B

  bool lessThan = max_ < otherManifold.min_;
  bool greaterThan = min_ > otherManifold.max_;

  if (lessThan || greaterThan)
  {
    //#Note This is if they are touching
    //if (min_ == otherManifold.max_ || max_ == otherManifold.min_)
    //{
    //  return CollisionStatus::TOUCHING;
    //}

    return CollisionStatus::NOT_COLLIDING;
  }

  return CollisionStatus::COLLIDING;
}

float CollisionManifold::GetPenetration(const CollisionManifold& a, const CollisionManifold& b)
{
  // min > otherManifold.min
  //        b-------a-B------A
  // min < othermanifold.min
  //a-------b-A-------B
  return a.max_ - b.min_;
}
