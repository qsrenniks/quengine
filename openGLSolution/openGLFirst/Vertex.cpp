#include "stdafx.h"
#include "Vertex.h"

Vertex::Vertex(float x, float y, float z)
{
  position_.x = x;
  position_.y = y;
  position_.z = z;
}

glm::vec3 Vertex::operator-(const Vertex& rhs) 
{
  return position_ - rhs.position_;
}

Vertex::operator glm::vec3() const
{
  return position_;
}
