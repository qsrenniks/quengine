#include "stdafx.h"
#include "CollisionComponent.h"
#include "GameObjectSystem.h"
#include "Engine.h"
#include "IGameObject.h"

CollisionComponent::CollisionComponent(CollisionProfile *profile /*= nullptr*/)
  : collisionProfile_(profile)
{

}

CollisionComponent::~CollisionComponent()
{
  GameObjectSystem* sys = Engine::Instance()->GetSystem<GameObjectSystem>();
  sys->RemoveCollisonComponent(this);
}

void CollisionComponent::Update(float dt)
{

}

void CollisionComponent::Draw()
{

}

void CollisionComponent::Parent(class IGameObject * parent)
{
  IComponent::Parent(parent);

  GameObjectSystem* sys = Engine::Instance()->GetSystem<GameObjectSystem>();
  sys->AddCollisionComponent(this);
}

void CollisionComponent::Register()
{
  IGameObject* parent = GetParent();

  //i am not registering update function since collision component is updated differently.
  parent->GetDrawList().AddFunction(this, &CollisionComponent::Draw);
}

bool CollisionComponent::IsCollidingWith(CollisionComponent *otherCollider)
{
  return false;
}
