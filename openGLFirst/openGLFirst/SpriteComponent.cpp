#include "stdafx.h"
#include "SpriteComponent.h"
#include <glm/gtc/matrix_transform.hpp>
#include "IGameObject.h"
#include "Engine.h"

SpriteComponent::SpriteComponent(const char *vertexShader, const char *fragmentShader, glm::vec4 color, int z) 
  : IComponent(z)
  , shader_(vertexShader, fragmentShader)
  , color_(color)
{
  glGenBuffers(1, &VBO_);

  //unsigned int VAO;
  glGenVertexArrays(1, &VAO_);

  glGenBuffers(1, &EBO_);
}


SpriteComponent::~SpriteComponent()
{
}

void SpriteComponent::Draw()
{
  shader_.use();

  //binding the Vertex buffer object
  glBindBuffer(GL_ARRAY_BUFFER, VBO_);
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices_), &vertices_[0], GL_STATIC_DRAW);
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
  glEnableVertexAttribArray(0);

  //binding the Vertex array object
  glBindVertexArray(VAO_);
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
  glEnableVertexAttribArray(0);

  //EBO setup
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO_);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices_), indices_, GL_STATIC_DRAW);
  
  //set engine camera transform


  shader_.setMat4("view", glm::inverse(Engine::Instance()->GetViewTransform()));
  shader_.setMat4("transform", GetParent()->GetTransform());
  shader_.setVec4("aColor", color_);

  //number of vert draws
  glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}

void SpriteComponent::Update(float dt)
{

}