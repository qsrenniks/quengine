#include "stdafx.h"
#include "Mesh.h"

Mesh::Mesh(float width, float height)
  : width_(width)
  , height_(height)
{
  float halfWidth = width_ / 2.0f;
  float halfHeight = height_ / 2.0f;

  vertices_[0][0] = halfWidth;
  vertices_[0][1] = halfHeight;
  vertices_[0][2] = 0.0f;
  vertices_[1][0] = halfWidth;
  vertices_[1][1] = -halfHeight;
  vertices_[1][2] = 0.0f;
  vertices_[2][0] = -halfWidth;
  vertices_[2][1] = -halfHeight;
  vertices_[2][2] = 0.0f;
  vertices_[3][0] = -halfWidth;
  vertices_[3][1] = halfHeight;
  vertices_[3][2] = 0.0f;

  glGenBuffers(1, &VBO_);

  //unsigned int VAO;
  glGenVertexArrays(1, &VAO_);

  glGenBuffers(1, &EBO_);
}

Mesh::~Mesh()
{
}

void Mesh::Draw()
{
  //binding the Vertex buffer object
  glBindBuffer(GL_ARRAY_BUFFER, VBO_);
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices_), &vertices_[0], GL_STATIC_DRAW);
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
  glEnableVertexAttribArray(0);

  //binding the Vertex array object
  glBindVertexArray(VAO_);
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
  glEnableVertexAttribArray(0);

  //EBO setup
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO_);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices_), indices_, GL_STATIC_DRAW);

  //number of vert draws
  glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}

glm::vec2 Mesh::GetWidthHeight()
{
  return glm::vec2(width_, height_);
}
