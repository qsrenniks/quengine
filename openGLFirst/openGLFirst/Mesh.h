#pragma once
#include "glm/vec2.hpp"
#include "glm/mat4x4.hpp"
#include <vector>

class SpriteComponent;

class Mesh
{
public:
  enum MeshCorner
  {
    TOP_LEFT = 0, 
    TOP_RIGHT, 
    BOTTOM_LEFT, 
    BOTTOM_RIGHT
  };

  Mesh(SpriteComponent* spriteComponent, float width, float height);
  ~Mesh();

  void Draw();
  
  glm::vec2 GetWidthHeight();

  glm::vec2 GetVertPos(MeshCorner corner, const glm::mat4& matrix);

  SpriteComponent* GetSpriteComponent();

  struct Projection
  {
    bool IsOverlapping(const Projection& otherProjections);
    float GetOverlap(const Projection& otherProjection);
    float min_;
    float max_;
    glm::vec2 projection_;
  };

  Projection project(const glm::vec2& lineToProjectOn);

  void GetAxis(std::vector<glm::vec2>& axis, const glm::mat4& matrix);

private:

  float project(const glm::vec2& point, const glm::vec2& line) const;

  SpriteComponent* spriteComponent_;

  float width_;
  float halfWidth_;
  float height_;
  float halfHeight_;

  unsigned int VAO_;
  unsigned int VBO_;
  unsigned int EBO_;

  float vertices_[4][3];

  unsigned int indices_[6] =
  {
    0, 1, 3, 1, 2, 3
  };

};

