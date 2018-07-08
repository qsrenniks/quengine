#include "stdafx.h"
#include "Mesh.h"
#include "SpriteComponent.h"
#include "IGameObject.h"

#define GLM_ENABLE_EXPERIMENTAL
#include "glm/gtx/rotate_vector.hpp"

Mesh::Mesh(SpriteComponent *spriteComponent, float width, float height)
  : spriteComponent_(spriteComponent)
  , width_(width)
  , halfWidth_(width / 2.0f)
  , height_(height)
  , halfHeight_(height / 2.0f)
{
  vertices_[0][0] = halfWidth_;
  vertices_[0][1] = halfHeight_;
  vertices_[0][2] = 0.0f;
  vertices_[1][0] = halfWidth_;
  vertices_[1][1] = -halfHeight_;
  vertices_[1][2] = 0.0f;
  vertices_[2][0] = -halfWidth_;
  vertices_[2][1] = -halfHeight_;
  vertices_[2][2] = 0.0f;
  vertices_[3][0] = -halfWidth_;
  vertices_[3][1] = halfHeight_;
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

glm::vec2 Mesh::GetVertPos(MeshCorner corner)
{
  glm::vec3 spritePosition = spriteComponent_->GetParent()->GetTransform().GetPosition();

  glm::vec2 rotatedHalfWidth = glm::rotate(glm::vec2(halfWidth_, halfHeight_), glm::radians(spriteComponent_->GetParent()->GetTransform().GetRotation()));
  
  glm::vec2 vertPos;

  switch (corner)
  {
  case MeshCorner::TOP_LEFT:
    vertPos = glm::vec2(spritePosition.x - halfWidth_, spritePosition.y + halfHeight_);
    break;
  case MeshCorner::TOP_RIGHT:
    vertPos = glm::vec2(spritePosition.x + halfWidth_, spritePosition.y + halfHeight_);
    break;
  case MeshCorner::BOTTOM_LEFT:
    vertPos = glm::vec2(spritePosition.x - halfWidth_, spritePosition.y - halfHeight_);
    break;
  case MeshCorner::BOTTOM_RIGHT:
    vertPos = glm::vec2(spritePosition.x + halfWidth_, spritePosition.y - halfHeight_);
    break;
  }

  return vertPos;
}

SpriteComponent * Mesh::GetSpriteComponent()
{
  return spriteComponent_;
}
