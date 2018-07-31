#include "stdafx.h"
#include "RigidBodyGameObject.h"
#include "TextLibrary.h"
#include "CollisionComponent.h"
#include "PhysicsComponent.h"
#include "Engine.h"
 
RigidBodyGameObject::RigidBodyGameObject()
{
  AddComponent<PhysicsComponent>(physics_);
  AddComponent<CollisionComponent>(collision_, new PolygonalCollisionProfile());

  GameObjectSystem* goSystem = Engine::Instance()->GetGameObjectSystem();
  goSystem->AddRigidBodyGameObject(this);
}

RigidBodyGameObject::~RigidBodyGameObject()
{
}

CollisionComponent* RigidBodyGameObject::GetCollisionComponent()
{
  return collision_;
}

PhysicsComponent* RigidBodyGameObject::GetPhysicsComponent()
{
  return physics_;
}
