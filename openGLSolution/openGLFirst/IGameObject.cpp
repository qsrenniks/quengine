#include "stdafx.h"
#include "IGameObject.h"
#include "Engine.h"
#include "SpriteComponent.h"

IGameObject::IGameObject()
{
  AddComponent<SpriteComponent>(sprite_, glm::vec4{ 1.0f, 1.0f, 1.0f, 1.0f }, 0);
}

IGameObject::~IGameObject()
{
}

//void IGameObject::OnObjectCreated()
//{
//  onObjectCreated_.Broadcast();
//}

void IGameObject::UpdateGameObject(float dt)
{
  //update components first
  componentUpdateList_.Broadcast(dt);
  //then game object since this may be dependent on the state of other components
  //gameObjectUpdateList_.Broadcast(dt);
  Update(dt);
  //then draw the game object to ensure it is in the correct position in the level.
  //componentDrawList_.Broadcast();
}

void IGameObject::DestroyGameObject()
{
  markForDestroy_ = true;
}

bool IGameObject::IsMarkedForDestroy()
{
  return markForDestroy_;
}

Transform& IGameObject::GetTransform()
{
  return transform_;
}

SpriteComponent* IGameObject::GetSpriteComponent()
{
  return sprite_;
}

delegate<void(float)>& IGameObject::GetComponentUpdateList()
{
  return componentUpdateList_;
}

delegate<void(void)>& IGameObject::GetDrawList()
{
  return componentDrawList_;
}
