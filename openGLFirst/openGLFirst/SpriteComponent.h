#pragma once
#include "IComponent.h"
#include "Shader.h"
#include "Vertices.h"
#include <vector>

class SpriteComponent : public IComponent
{
public:
  SpriteComponent(const char *vertexShader, const char *fragmentShader, glm::vec4 color, int z = 0);
  virtual ~SpriteComponent();

  virtual void Draw() override;
  virtual void Update(float dt) override;

private:
  unsigned int VAO_;
  unsigned int VBO_;
  unsigned int EBO_;

  glm::vec4 color_{1.0f};

  Shader shader_;

  //triangle setup
  std::vector<Vertices> vertices_{
    { 0.5f,  0.5f, 0.0f },  // top right
    {0.5f, -0.5f, 0.0f }, // bottom right
    {-0.5f, -0.5f, 0.0f},  // bottom left
    {-0.5f,  0.5f, 0.0f}   // top left 
  };

  unsigned int indices_[6] = {  // note that we start from 0!
    0, 1, 3,   // first triangle
    1, 2, 3    // second triangle
  };
};

