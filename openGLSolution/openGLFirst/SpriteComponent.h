#pragma once
#include "IComponent.h"
#include "Shader.h"
#include <vector>
#include "Mesh.h"

class SpriteComponent : public IComponent
{
public:
  SpriteComponent(glm::vec4 color, int z = 0, float width = 1.0f, float height = 1.0f);
  virtual ~SpriteComponent();

  //virtual void Draw() override;

  virtual void Update(float dt) override;

  virtual void Draw() override;

  const Mesh& GetMesh() const; 
  
  void SetColor(const glm::vec4& color);

  virtual void Serialize(rapidjson::Document& doc) override;
  virtual void Deserialize(rapidjson::Document& doc) override;

private:
  Shader spriteShader_;
  Mesh spriteMesh_;

  glm::vec4 color_{1.0f};

  //Shader shader_;
};

