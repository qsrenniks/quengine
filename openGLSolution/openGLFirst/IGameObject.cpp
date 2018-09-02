#include "stdafx.h"
#include "IGameObject.h"
#include "Engine.h"
#include "SpriteComponent.h"

IGameObject::IGameObject()
{
  AddComponent<SpriteComponent>(sprite_, glm::vec4{ 1.0f, 1.0f, 1.0f, 1.0f }, 0);
}

IGameObject::IGameObject(const glm::vec2& spawnLocation)
  : IGameObject()
{
  transform_.SetPosition(spawnLocation);
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
  //componentUpdateList_.Broadcast(dt);
  //run through components and update them
  for (auto& component : componentList_)
  {
    component->Update(dt);
  }

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

void IGameObject::Serialize(rapidjson::Document& doc)
{
  //serialize all components and their properties
  for (auto& component : componentList_)
  {
    component->Serialize(doc);
  }
}

void IGameObject::Deserialize(rapidjson::Document& doc)
{
  //deserialize all components and their properties
  for (auto& component : componentList_)
  {
    component->Deserialize(doc);
  }
}

void IGameObject::Draw()
{
  for (auto& component : componentList_)
  {
    component->Draw();
  }
}

Transform& IGameObject::GetTransform()
{
  return transform_;
}

//SpriteComponent* IGameObject::GetSpriteComponent()
//{
//  return sprite_;
//}

void IGameObject::SetLocation(const glm::vec2& newLocation)
{
  transform_.SetPosition(newLocation);
}

//
//Delegate<void(float)>& IGameObject::GetComponentUpdateList()
//{
//  return componentUpdateList_;
//}
//
//Delegate<void(void)>& IGameObject::GetDrawList()
//{
//  return componentDrawList_;
//}
