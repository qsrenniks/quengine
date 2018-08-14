#pragma once
#include "Vertex.h"
#include <utility>

enum class CollisionStatus : int;

class CollisionManifold
{
public:
  CollisionManifold(float min = 0.0f, float max = 0.0f);
  ~CollisionManifold();

  void ProjectVerticesOntoEdge(const glm::vec3& first, const glm::vec3& second, const glm::vec2& edge);

  CollisionStatus IsOverlapping(const CollisionManifold& otherManifold);

  static float GetPenetration(const CollisionManifold& a, const CollisionManifold& b);
private:
  float min_ = 0.0f;
  float max_ = 0.0f;
};

