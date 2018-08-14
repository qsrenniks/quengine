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

  using EdgeList = std::list<glm::vec2>;

public:

  Mesh() = default;
  Mesh(const std::vector<Vertex>& vertices, const std::vector<unsigned int>& indices);

  void Draw();

  std::vector<Vertex> vertices_;
  std::vector<unsigned int> indices_;
  void SetupMesh();

  EdgeList edgeNormals_;

  std::pair<Vertex, Vertex> farVertex_;

private:
  unsigned int vao_, vbo_, ebo_;

  void SetupEdgeNormals();
  void SetupFarVertex();
};

