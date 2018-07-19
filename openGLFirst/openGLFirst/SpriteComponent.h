#pragma once
#include "IComponent.h"
#include "Shader.h"
#include <vector>
#include "Mesh.h"

class SpriteComponent : public IComponent
{
public:
  SpriteComponent(const char *vertexShader, const char *fragmentShader, glm::vec4 color, int z = 0, float width = 1.0f, float height = 1.0f);
  virtual ~SpriteComponent();

  //virtual void Draw() override;
  virtual void Update(float dt) override;

  virtual void Draw() override;

  Mesh& GetMesh();
  
  void SetColor(const glm::vec4& color);

private:
  Mesh spriteMesh_;

  glm::vec4 color_{1.0f};

  Shader shader_;
};

