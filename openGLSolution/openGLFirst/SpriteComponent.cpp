#include "stdafx.h"
#include "SpriteComponent.h"
#include <glm/gtc/matrix_transform.hpp>
#include "IGameObject.h"
#include "Engine.h"


SpriteComponent::SpriteComponent(glm::vec4 color, int z, float width, float height) 
  : IComponent(z)
  , spriteMesh_(this, width, height)
  , color_(color)
{

}


SpriteComponent::~SpriteComponent()
{
}

void SpriteComponent::Draw()
{
  Engine::Instance()->GetRenderingSystem()->DrawSquare(GetParent()->GetTransform().BuildTransform(), color_);
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