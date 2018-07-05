#pragma once
#include "glm/vec2.hpp"

class Mesh
{
public:
  Mesh(float width, float height);
  ~Mesh();

  void Draw();
  
  glm::vec2 GetWidthHeight();

private:
  float width_;
  float height_;

  unsigned int VAO_;
  unsigned int VBO_;
  unsigned int EBO_;

  float vertices_[4][3];

  unsigned int indices_[6] =
  {
    0, 1, 3,
    1, 2, 3
  };

};

