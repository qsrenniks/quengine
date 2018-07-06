#include "stdafx.h"
#include "IGameObject.h"
#include "Engine.h"

IGameObject::IGameObject() 
{
  gameObjectUpdateList_.AddFunction(this, &IGameObject::Update);
}

IGameObject::~IGameObject()
{
  for (auto component : componentList_)
  {
    delete component;
  }
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

delegate<void(float)>& IGameObject::GetUpdateList()
{
  return gameObjectUpdateList_;
}

delegate<void(float)>& IGameObject::GetComponentUpdateList()
{
  return componentUpdateList_;
}

delegate<void(void)>& IGameObject::GetDrawList()
{
  return componentDrawList_;
}