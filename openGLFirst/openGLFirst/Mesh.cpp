#include "stdafx.h"
#include "Mesh.h"
#include "SpriteComponent.h"
//#include "IGameObject.h"

#define GLM_ENABLE_EXPERIMENTAL
#include "glm/gtx/rotate_vector.hpp"

Mesh::Mesh(SpriteComponent* spriteComponent, float width, float height)
  : spriteComponent_(spriteComponent)
  , width_(width)
  , halfWidth_(width / 2.0f)
  , height_(height)
  , halfHeight_(height / 2.0f)
{
  // 0
  vertices_[0][0] = halfWidth_;
  vertices_[0][1] = halfHeight_;
  // 1
  vertices_[0][2] = 0.0f;
  vertices_[1][0] = halfWidth_;
  // 2
  vertices_[1][1] = -halfHeight_;
  vertices_[1][2] = 0.0f;
  // 3
  vertices_[2][0] = -halfWidth_;
  vertices_[2][1] = -halfHeight_;
  // 4
  vertices_[2][2] = 0.0f;
  vertices_[3][0] = -halfWidth_;
  //5
  vertices_[3][1] = halfHeight_;
  vertices_[3][2] = 0.0f;

  glGenBuffers(1, &VBO_);

  //unsigned int VAO;
  glGenVertexArrays(1, &VAO_);

  glGenBuffers(1, &EBO_);
}

Mesh::~Mesh()
{
  glDeleteVertexArrays(1, &VAO_);
  glDeleteBuffers(1, &VBO_);
  glDeleteBuffers(1, &EBO_);
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

glm::vec2 Mesh::GetVertPos(MeshCorner corner, const glm::mat4& matrix)
{
  switch (corner)
  {
  case MeshCorner::TOP_LEFT:
    return matrix * glm::vec4(glm::vec2(-halfWidth_, halfHeight_),0.0f,1.0f);
  case MeshCorner::TOP_RIGHT:
    return matrix * glm::vec4(glm::vec2(halfWidth_, halfHeight_), 0.0f, 1.0f);
  case MeshCorner::BOTTOM_LEFT:
    return matrix * glm::vec4(glm::vec2(-halfWidth_, -halfHeight_), 0.0f, 1.0f);
  case MeshCorner::BOTTOM_RIGHT:
    return matrix * glm::vec4(glm::vec2(+halfWidth_, -halfHeight_), 0.0f, 1.0f);
  }

  return glm::vec2();
}

SpriteComponent* Mesh::GetSpriteComponent()
{
  return spriteComponent_;
}

Mesh::Projection Mesh::project(const glm::vec2& lineToProjectOn)
{
  Transform& objTransform = spriteComponent_->GetParent()->GetTransform();
  auto matrix = objTransform.BuildTransform();

  float min = project(GetVertPos(TOP_LEFT, matrix), lineToProjectOn);
  float max = min;

  for (int i = 0; i < 4; i++)
  {
    float projectionPoint = project(GetVertPos((MeshCorner)i, matrix), lineToProjectOn);
    if (projectionPoint < min)
    {
      min = projectionPoint;
    }
    else if (projectionPoint > max)
    {
      max = projectionPoint;
    }
  }

  Projection projection;

  projection.min_ = min;
  projection.max_ = max;

  projection.projection_ = glm::vec2(lineToProjectOn.x * min, lineToProjectOn.y * max);

  return projection;
}

float Mesh::project(const glm::vec2& point, const glm::vec2& line) const
{
  return glm::dot(point, line);
}

void Mesh::GetAxis(std::vector<glm::vec2>& axis, const glm::mat4& matrix)
{
  glm::vec2 topLeft = GetVertPos(TOP_LEFT, matrix);
  glm::vec2 topRight = GetVertPos(TOP_RIGHT, matrix);
  glm::vec2 bottomRight = GetVertPos(BOTTOM_RIGHT, matrix);
  glm::vec2 bottomLeft = GetVertPos(BOTTOM_LEFT, matrix);

  glm::vec2 topEdge = topRight - topLeft;
  glm::vec2 rightEdge = bottomRight - topRight;
  glm::vec2 bottomEdge = bottomLeft - bottomRight;
  glm::vec2 leftEdge = topLeft - bottomLeft;

  //rotate them 
  std::swap(topEdge.x, topEdge.y);
  topEdge.x *= -1;

  std::swap(rightEdge.x, rightEdge.y);
  rightEdge.x *= -1;

  std::swap(bottomEdge.x, bottomEdge.y);
  bottomEdge.x *= -1;

  std::swap(leftEdge.x, leftEdge.y);
  leftEdge.x *= -1;

  axis.push_back(topEdge);
  axis.push_back(rightEdge);
  axis.push_back(bottomEdge);
  axis.push_back(leftEdge);

}

CollisionOccurence::CollisionStatus Mesh::Projection::IsOverlapping(const Projection& otherProjections)
{
  bool lessThan = max_ <= otherProjections.min_;
  bool greaterThan = min_ >= otherProjections.max_;

  if (lessThan || greaterThan)
  {
    if (max_ == otherProjections.min_ || min_ == otherProjections.max_)
    {
      return CollisionOccurence::CollisionStatus::TOUCHING;
    }

    return CollisionOccurence::CollisionStatus::NOT_COLLIDING;
  }

  return CollisionOccurence::CollisionStatus::COLLIDING;
}

float Mesh::Projection::GetOverlap(const Projection& otherProjection)
{
  if (max_ > otherProjection.min_) 
  {
    return max_ - otherProjection.min_;
  }
  else if (min_ > otherProjection.max_) 
  {
    return min_ - otherProjection.max_;
  }
  return 0;
}
