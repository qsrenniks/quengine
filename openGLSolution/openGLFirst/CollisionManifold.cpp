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

void CollisionManifold::ProjectVerticesOntoEdge(const std::vector<Vertex>& verticeList, const glm::mat4& transformMat, const glm::vec2& edge)
{
  //this projects all vertices onto the edge specified. then grabs the min and the max from the projection
  float min = std::numeric_limits<float>::max();
  float max = -std::numeric_limits<float>::max();
  
  for (const Vertex& vert : verticeList)
  {
    glm::vec2 transformVert = glm::vec2(transformMat * glm::vec4(glm::vec3(vert), 1.0f));

    float projectedVert = glm::dot(transformVert, edge);

    if (projectedVert < min)
    {
      min = projectedVert;
    }
    if (projectedVert >= max)
    {
      max = projectedVert;
    }
  }

  min_ = min;
  max_ = max;
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
