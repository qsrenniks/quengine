#pragma once
#include <glm/glm.hpp>
#include <vector>
#include "Vertices.h"
#include "Shader.h"

class Mesh
{
public:

  Mesh(float width, float height, const char *vertexShader, const char *fragmentShader, glm::vec4 color, int z = 0);

private:
  unsigned int VAO_;
  unsigned int VBO_;
  unsigned int EBO_;

  glm::vec4 color_{ 1.0f };

  Shader shader_;

  Vertices vertices_[4] = 
  {
    { 0.5f,  0.5f, 0.0f },
    { 0.5f, -0.5f, 0.0f },
    { -0.5f, -0.5f, 0.0f },
    { -0.5f,  0.5f, 0.0f },
  };

  unsigned int indices_[6] = 
  {
    0, 1, 3,
    1, 2, 3
  };
};