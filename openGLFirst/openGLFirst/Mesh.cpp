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

  edgeNormals_.assign(4, glm::vec2(0.0f, 0.0f));
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

void Mesh::GetWidthHeight(glm::vec2& widthHeight)
{
  widthHeight.x = width_;
  widthHeight.y = height_;
}

void Mesh::GetVertPos(MeshCorner corner, const glm::mat4& matrix, glm::vec2& vertPosition)
{
  switch (corner)
  {
  case MeshCorner::TOP_LEFT:
    vertPosition = matrix * glm::vec4(-halfWidth_, halfHeight_, 0.0f, 1.0f);
    break;
  case MeshCorner::TOP_RIGHT:
    vertPosition = matrix * glm::vec4(halfWidth_, halfHeight_, 0.0f, 1.0f);
    break;
  case MeshCorner::BOTTOM_LEFT:
    vertPosition = matrix * glm::vec4(-halfWidth_, -halfHeight_, 0.0f, 1.0f);
    break;
  case MeshCorner::BOTTOM_RIGHT:
    vertPosition = matrix * glm::vec4(halfWidth_, -halfHeight_, 0.0f, 1.0f);
    break;
  default:
    vertPosition.x = 0.0f;
    vertPosition.y = 0.0f;
    break;
  }
}

SpriteComponent* Mesh::GetSpriteComponent()
{
  return spriteComponent_;
}

void Mesh::CalculateEdgeNormals()
{
  glm::vec2 topLeft;
  glm::vec2 topRight;
  glm::vec2 bottomRight;
  glm::vec2 bottomLeft;
  
  const glm::mat4& matrix = GetSpriteComponent()->GetParent()->GetTransform().BuildTransform();

  GetVertPos(TOP_LEFT, matrix, topLeft);
  GetVertPos(TOP_RIGHT, matrix, topRight);
  GetVertPos(BOTTOM_RIGHT, matrix, bottomRight);
  GetVertPos(BOTTOM_LEFT, matrix, bottomLeft);

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

  edgeNormals_[0] = glm::normalize(topEdge);
  edgeNormals_[1] = glm::normalize(rightEdge);
  edgeNormals_[2] = glm::normalize(bottomEdge);
  edgeNormals_[3] = glm::normalize(leftEdge);
}

void Mesh::Project(const glm::vec2& lineToProjectOn, Projection& projection)
{
  Transform& objTransform = spriteComponent_->GetParent()->GetTransform();
  auto matrix = objTransform.BuildTransform();

  glm::vec2 vertPosition(0.0f, 0.0f);
  GetVertPos(TOP_LEFT, matrix, vertPosition);

  float min = Project(vertPosition, lineToProjectOn);
  float max = min;

  for (int i = 1; i < 4; i++)
  {    
    GetVertPos((MeshCorner)i, matrix, vertPosition);
    float projectionPoint = Project(vertPosition, lineToProjectOn);

    if (projectionPoint < min)
    {
      min = projectionPoint;
    }
    else if (projectionPoint > max)
    {
      max = projectionPoint;
    }
  }

  projection.min_ = min;
  projection.max_ = max;

  projection.projection_ = glm::vec2(lineToProjectOn.x * min, lineToProjectOn.y * max);
}

float Mesh::Project(const glm::vec2& point, const glm::vec2& line) const
{
  return glm::dot(point, line);
}

const std::vector<glm::vec2>& Mesh::GetAxis()
{
  //there might be an optimization to do here. If and only if the object has been rotated do the edge normals ever change.
  CalculateEdgeNormals();

  return edgeNormals_;
}

CollisionOccurence::CollisionStatus Mesh::Projection::IsOverlapping(const Projection& otherProjections)
{
  bool lessThan = max_ < otherProjections.min_;
  bool greaterThan = min_ > otherProjections.max_;

  if (lessThan || greaterThan)
  {
    return CollisionOccurence::CollisionStatus::NOT_COLLIDING;
  }

  //
  //if (glm::epsilonEqual(max_, otherProjections.min_, 0.005f) || glm::epsilonEqual(min_, otherProjections.max_, 0.005f))
  //{
  //  return CollisionOccurence::CollisionStatus::TOUCHING;
  //}
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
