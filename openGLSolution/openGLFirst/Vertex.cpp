#include "stdafx.h"
#include "Vertex.h"

Vertex::Vertex(float x, float y, float z)
{
  position_.x = x;
  position_.y = y;
  position_.z = z;
}

Vertex::Vertex(const glm::vec2& vec)
{
  position_.x = vec.x;
  position_.y = vec.y;
  position_.z = 0.0f;
}

glm::vec3 Vertex::operator-(const Vertex& rhs) const
{
  return position_ - rhs.position_;
}

Vertex::operator glm::vec3() const
{
  return position_;
}
