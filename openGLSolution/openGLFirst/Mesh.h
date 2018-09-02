#pragma once

#include "IGameObject.h"
#include "GameObjectSystem.h"
#include "glm/vec2.hpp"
#include "glm/mat4x4.hpp"
#include "Vertex.h"
#include <vector>

class SpriteComponent;
enum class CollisionStatus : int;

class Mesh
{
public: //Types

  using EdgeList = std::vector<glm::vec2>;

public:

  Mesh() = default;
  Mesh(const std::vector<Vertex>& vertices, const std::vector<unsigned int>& indices);

  void Draw();

  std::vector<Vertex> relativeVertices_;
  std::vector<unsigned int> indices_;
  void SetupMesh();
  void ResetMesh();
  void RecalculateEdgeNormals(float newRotationR);

  EdgeList transformedEdgeNormals_;
  EdgeList edgeNormals_;

  std::pair<Vertex, Vertex> farVertex_;

private:

  glm::vec2 CalculateEdgeNormal(const Vertex& a, const Vertex& b) const;

  bool isDirty_ = true;

  unsigned int vao_, vbo_, ebo_;

  void SetupEdgeNormals();
  void SetupFarVertex();
};

