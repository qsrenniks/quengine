#include "stdafx.h"
#include "RigidBodyComponent.h"
#include "IGameObject.h"
#include "GameObjectSystem.h"
#include "Engine.h"
#include "PhysicsComponent.h"
#include "CollisionComponent.h"
#include "BPCollisionProfile.h"
#include "NPCollisionProfile.h"
#include "MeshDescriptions.h"

RigidBodyComponent::RigidBodyComponent(float bounce /*= 0.0f*/)
  : bounce_(bounce)
{

}

RigidBodyComponent::~RigidBodyComponent()
{
  GameObjectSystem* goSys = Engine::Instance()->GetGameObjectSystem();
  goSys->RemoveRigidBodyComponent(this);
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
  NPCollisionProfile* collisionProfile = new NPCollisionProfile(Shapes::Square_Vertices, Shapes::Square_Indices);

  parent->AddComponent<PhysicsComponent>(physics_);
  parent->AddComponent<CollisionComponent>(collision_, collisionProfile, new BPCollisionProfile(glm::vec2(1.0f, 1.0f)));
}

PhysicsComponent* RigidBodyComponent::GetPhysicsComponent()
{
  return physics_;
}

CollisionComponent* RigidBodyComponent::GetCollisionComponent()
{
  return collision_;
}

void RigidBodyComponent::UpdateCollisionWith(RigidBodyComponent* otherBody, CollisionStatus status)
{
  //this is where we broadcast the status delegates
  bool isUnique = IsBodyUnique(otherBody);

  if (isUnique && status != CollisionStatus::NOT_COLLIDING)
  {
    onCollisionEnter_.Broadcast(otherBody);
    //TODO: this could be greatly improved with a max overlaps feature.
    rigidBodyCollisions_.push_back(otherBody);
  }
  else if(isUnique == false && status == CollisionStatus::NOT_COLLIDING)
  {
    onCollisionExit_.Broadcast(otherBody);
    rigidBodyCollisions_.remove(otherBody);
  }
}

RigidBodyComponent::CollisionList& RigidBodyComponent::GetOverlappingBodies()
{
  return rigidBodyCollisions_;
}

void RigidBodyComponent::Serialize(rapidjson::Document& doc)
{
}

void RigidBodyComponent::Deserialize(rapidjson::Document& doc)
{
}

bool RigidBodyComponent::IsBodyUnique(RigidBodyComponent* otherBody)
{
  //if it equals end it did not find the body so it is unique
  if (std::find(rigidBodyCollisions_.begin(), rigidBodyCollisions_.end(), otherBody) == rigidBodyCollisions_.end())
  {
    return true;
  }
  return false;
}
