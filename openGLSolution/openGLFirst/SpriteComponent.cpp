#include "stdafx.h"
#include "SpriteComponent.h"
#include <glm/gtc/matrix_transform.hpp>
#include "IGameObject.h"
#include "Engine.h"


SpriteComponent::SpriteComponent(glm::vec4 color, int z, float width, float height) 
  : IComponent(z)
  , spriteShader_(R"(..\vertexShader.vs)", R"(..\fragmentShader.fs)")
  , spriteMesh_()
  , color_(color)
{
  spriteMesh_.relativeVertices_ = 
  {
    {  0.5f * width,  0.5f * height, 0.0f }, //top right
    {  0.5f * width, -0.5f * height, 0.0f }, //bottom right
    { -0.5f * width, -0.5f * height, 0.0f }, //bottom left
    { -0.5f * width,  0.5f * height, 0.0f } //top left
  };

  spriteMesh_.indices_ = { 0, 1, 3, 1, 2, 3 };

  spriteMesh_.SetupMesh();

  spriteShader_.init();
}

SpriteComponent::~SpriteComponent()
{
}

void SpriteComponent::Draw()
{
  //Engine::Instance()->GetRenderingSystem()->DrawSquare(GetParent()->GetTransform().BuildTransform(), color_);
  spriteShader_.use();

  spriteShader_.setMat4("model", GetParent()->GetTransform().BuildTransform());
  spriteShader_.setVec4("aColor", color_);

  spriteShader_.setMat4("projection", Engine::Instance()->GetOrthographicTransform());
  spriteShader_.setMat4("view", Engine::Instance()->GetViewTransform().BuildTransform());

  spriteMesh_.Draw();
}

const Mesh& SpriteComponent::GetMesh() const
{
  return spriteMesh_;
}

void SpriteComponent::SetColor(const glm::vec4& color)
{
  color_ = color;
}

void SpriteComponent::Serialize(rapidjson::Document& doc)
{
  using namespace rapidjson;

  Value spriteComponent(kObjectType);
  Value color(kObjectType);

  color.AddMember("r", color_.r, doc.GetAllocator());
  color.AddMember("g", color_.b, doc.GetAllocator());
  color.AddMember("b", color_.g, doc.GetAllocator());
  color.AddMember("a", color_.a, doc.GetAllocator());
  spriteComponent.AddMember("Sprite Color", color, doc.GetAllocator());

  doc.AddMember("Sprite Component", spriteComponent, doc.GetAllocator());
}

void SpriteComponent::Deserialize(rapidjson::Document& doc)
{

}

void SpriteComponent::Update(float dt)
{
}