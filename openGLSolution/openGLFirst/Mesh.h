#pragma once

#include "IGameObject.h"
#include "GameObjectSystem.h"
#include "glm/vec2.hpp"
#include "glm/mat4x4.hpp"
#include "Vertex.h"
#include <vector>

class SpriteComponent;
enum class CollisionStatus : int;



class Mesh
{
public:

  Mesh() = default;
  Mesh(const std::vector<Vertex>& vertices, const std::vector<unsigned int>& indices);

  void Draw();

  std::vector<Vertex> vertices_;
  std::vector<unsigned int> indices_;
  void SetupMesh();

private:
  unsigned int vao_, vbo_, ebo_;


  //#Note class is being refurbished
  //enum MeshCorner
  //{
  //  TOP_LEFT = 0, 
  //  TOP_RIGHT, 
  //  BOTTOM_LEFT, 
  //  BOTTOM_RIGHT
  //};

  //Mesh(SpriteComponent* spriteComponent, float width, float height);
  //~Mesh();

  //void GetWidthHeight(glm::vec2& widthHeight);

  //void GetVertPos(MeshCorner corner, const glm::mat4& matrix, glm::vec2& vertPosition);

  //SpriteComponent* GetSpriteComponent();

  //struct Projection
  //{
  //  CollisionStatus IsOverlapping(const Projection& otherProjections);
  //  float GetOverlap(const Projection& otherProjection);
  //  float min_;
  //  float max_;
  //  glm::vec2 projection_;
  //};

  //void Project(const glm::vec2& lineToProjectOn, Projection& projection);

  //const std::vector<glm::vec2>& GetAxis();

  //void CalculateEdgeNormals();
//private:


  //float Project(const glm::vec2& point, const glm::vec2& line) const;

  //SpriteComponent* spriteComponent_;

  //std::vector<glm::vec2> edgeNormals_;

  //float width_;
  //float halfWidth_;
  //float height_;
  //float halfHeight_;

  //unsigned int VAO_;
  //unsigned int VBO_;
  //unsigned int EBO_;

  //float vertices_[4][3];

  //unsigned int indices_[6] =
  //{
  //  0, 1, 3, 1, 2, 3
  //};

};

