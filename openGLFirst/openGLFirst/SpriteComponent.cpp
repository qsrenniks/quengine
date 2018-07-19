#include "stdafx.h"
#include "SpriteComponent.h"
#include <glm/gtc/matrix_transform.hpp>
#include "IGameObject.h"
#include "Engine.h"


SpriteComponent::SpriteComponent(const char *vertexShader, const char *fragmentShader, glm::vec4 color, int z, float width, float height) 
  : IComponent(z)
  , spriteMesh_(this, width, height)
  , shader_(vertexShader, fragmentShader)
  , color_(color)
{
}


SpriteComponent::~SpriteComponent()
{
}

void SpriteComponent::Draw()
{
  shader_.use();

  //shader_.setMat4("view", glm::inverse(Engine::Instance()->GetViewTransform()));
  shader_.setMat4("transform", GetParent()->GetTransform().BuildTransform());
  shader_.setVec4("aColor", color_);

  spriteMesh_.Draw();
}

Mesh& SpriteComponent::GetMesh()
{
  return spriteMesh_;
}

void SpriteComponent::SetColor(const glm::vec4& color)
{
  color_ = color;
}

void SpriteComponent::Update(float dt)
{
}