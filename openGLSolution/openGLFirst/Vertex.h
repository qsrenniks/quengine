#pragma once
class Vertex
{
public:

  Vertex(float x = 0.0f, float y = 0.0f, float z = 0.0f);
  Vertex(const glm::vec2& vec);
  glm::vec3 operator-(const Vertex& rhs) const;

  operator glm::vec3() const;
  
  glm::vec3 position_;
  //glm::vec3 normal_;
  //glm::vec2 TexCoords_;
};

