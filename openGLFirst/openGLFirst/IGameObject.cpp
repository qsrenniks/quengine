#include "IGameObject.h"
#include "Engine.h"

IGameObject::IGameObject() 
  : transform_(1.0f)
{
  gameObjectUpdateList_.AddFunction(this, &IGameObject::Update);
}

IGameObject::~IGameObject()
{
}

void IGameObject::UpdateGameObject(float dt)
{
  //update components first
  componentUpdateList_.broadcast(dt);
  //then game object since this may be dependent on the state of other components
  gameObjectUpdateList_.broadcast(dt);
  //then draw the game object to ensure it is in the correct position in the level.
  componentDrawList_.broadcast();
}

glm::mat4& IGameObject::GetTransform()
{
  return transform_;
}