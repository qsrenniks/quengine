#pragma once
class Vertex
{
public:

  Vertex(float x = 0.0f, float y = 0.0f, float z = 0.0f);
  
  glm::vec3 operator-(const Vertex& rhs);

  operator glm::vec3() const;

  glm::vec3 position_;
  //glm::vec3 normal_;
  //glm::vec2 TexCoords_;
};

