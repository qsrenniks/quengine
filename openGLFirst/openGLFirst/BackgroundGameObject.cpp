#include "BackgroundGameObject.h"
#include "SpriteComponent.h"

BackgroundGameObject::BackgroundGameObject()
{
  SpriteComponent *sprite = new SpriteComponent("vertexShader.vs", "fragmentShader.fs", glm::vec4{0.0f, 1.0f, 1.0f, 1.0f});
  //TransformComponent *transform = new TransformComponent();


  AddComponent(sprite);
  //AddComponent(transform);
}

BackgroundGameObject::~BackgroundGameObject()
{

}

void BackgroundGameObject::Update(float dt)
{

}