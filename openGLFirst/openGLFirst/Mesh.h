#pragma once
#include <glm/glm.hpp>
#include <vector>
#include "Vertices.h"
#include "Shader.h"

class Mesh
{
public:

  Mesh();

  void AddVertexToMesh(float x, float y, float z);

  size_t GetVerticeSize();
  size_t GetIndicesSize();

  void *GetVerticeAddress();
  void *GetIndicesAddress();

  unsigned int GetVAO();
  unsigned int GetVBO();
  unsigned int GetEBO();

private:
  unsigned int VAO_;
  unsigned int VBO_;
  unsigned int EBO_;

  std::vector<Vertices> vertices_;

  std::vector<unsigned int> indices_;
};