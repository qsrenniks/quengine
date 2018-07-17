#include "stdafx.h"
#include "IGameObject.h"
#include "Engine.h"

IGameObject::IGameObject() 
{
  //gameObjectUpdateList_.AddFunction(this, &IGameObject::Update);
}

IGameObject::~IGameObject()
{
  for (auto comp : componentList_)
  {
    delete comp;
  }
}

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

//CollisionOccurence IGameObject::GetCollisionOccurence()
//{
//  return CollisionOccurence();
//}

//
//delegate<void(float)>& IGameObject::GetUpdateList()
//{
//  return gameObjectUpdateList_;
//}

delegate<void(float)>& IGameObject::GetComponentUpdateList()
{
  return componentUpdateList_;
}

delegate<void(void)>& IGameObject::GetDrawList()
{
  return componentDrawList_;
}

bool CollisionOccurence::IsValid()
{
  return isValid_;
}


void CollisionOccurence::SetValid(bool validity)
{
  isValid_ = validity;
}
