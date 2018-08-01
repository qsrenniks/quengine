#include "stdafx.h"
#include "RigidBodyComponent.h"
#include "GameObjectSystem.h"
#include "Engine.h"
#include "PhysicsComponent.h"
#include "CollisionComponent.h"

RigidBodyComponent::RigidBodyComponent(float bounce /*= 0.0f*/)
  : bounce_(bounce)
{

}

RigidBodyComponent::~RigidBodyComponent()
{

}

void RigidBodyComponent::Update(float dt)
{

}

void RigidBodyComponent::Draw()
{

}

void RigidBodyComponent::Register()
{
  IComponent::Register();

  //register self with go system.
  GameObjectSystem* goSys = Engine::Instance()->GetGameObjectSystem();
  goSys->RegisterRigidBodyComponent(this);
}

void RigidBodyComponent::Parent(IGameObject* parent)
{
  IComponent::Parent(parent);

  //these go here and not in construction since you need the parent to create the game objects
  parent->AddComponent<PhysicsComponent>(physics_);
  parent->AddComponent<CollisionComponent>(collision_, new PolygonalCollisionProfile());
}

PhysicsComponent* RigidBodyComponent::GetPhysicsComponent()
{
  return physics_;
}

CollisionComponent* RigidBodyComponent::GetCollisionComponent()
{
  return collision_;
}
