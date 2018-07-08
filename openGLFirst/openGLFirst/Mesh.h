#pragma once
#include "glm/vec2.hpp"

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

  Mesh(SpriteComponent *spriteComponent, float width, float height);
  ~Mesh();

  void Draw();
  
  glm::vec2 GetWidthHeight();

  glm::vec2 GetVertPos(MeshCorner corner);

  SpriteComponent *GetSpriteComponent();

private:
  SpriteComponent *spriteComponent_;

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
    0, 1, 3,
    1, 2, 3
  };

};

