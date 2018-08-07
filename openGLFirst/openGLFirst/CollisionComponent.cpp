#include "stdafx.h"
#include "CollisionComponent.h"
//#include "GameObjectSystem.h"
#include "Engine.h"
//#include "IGameObject.h"
#include "SpriteComponent.h"
#include <iostream>
#include <algorithm>
#include "CollisionOccurence.h"
#include "PhysicsComponent.h"
#include "RigidBodyComponent.h"

CollisionComponent::CollisionComponent(CollisionProfile* profile/*, CollisionResponse* collisionResponse*/)
  : collisionProfile_(profile)
  //, collisionResponse_(collisionResponse)
{
  collisionProfile_->SetCollisionComponent(this);
  //collisionResponse_->SetCollisionComponent(this);
}

CollisionComponent::~CollisionComponent()
{
  //GameObjectSystem* sys = Engine::Instance()->GetGameObjectSystem();
  //sys->RemoveCollisonComponent(this);

  delete collisionProfile_;
  //delete collisionResponse_;
}

void CollisionComponent::Update(float dt)
{
  //if (isOverlappingWithSomething_)
  //{
  //  onUpdateOverlap_.Broadcast(overlappingColliders_);
  //}
}

void CollisionComponent::Draw()
{

}

//void CollisionComponent::Parent(IGameObject* parent)
//{
//  IComponent::Parent(parent);
//
//  GameObjectSystem* sys = Engine::Instance()->GetGameObjectSystem();
//  sys->AddCollisionComponent(this);
//} 

void CollisionComponent::Register()
{
  IGameObject* parent = GetParent();

  //i am not registering update function since collision component is updated differently.
  parent->GetDrawList().AddFunction(this, &CollisionComponent::Draw);
  parent->GetComponentUpdateList().AddFunction(this, &CollisionComponent::Update);
}

void CollisionComponent::IsCollidingWith(CollisionComponent* otherCollider, CollisionOccurence& collOcc) const
{
  collisionProfile_->IsProfileCollidingWith(otherCollider->collisionProfile_, collOcc);
}

PolygonalCollisionProfile::PolygonalCollisionProfile()
{
}

void PolygonalCollisionProfile::IsProfileCollidingWith(CollisionProfile* otherProfile, CollisionOccurence& collOcc) const
{
  IGameObject* objectA = collisionComponent_->GetParent();
  IGameObject* objectB = otherProfile->GetCollisionComponent()->GetParent();

  assert(objectA != nullptr && objectB != nullptr);

  SpriteComponent* spriteA = objectA->GetComponent<SpriteComponent>();
  SpriteComponent* spriteB = objectB->GetComponent<SpriteComponent>();

  //get meshes
  Mesh& meshA = spriteA->GetMesh();
  Mesh& meshB = spriteB->GetMesh();

  Transform& transformA = spriteA->GetParent()->GetTransform();
  Transform& transformB = spriteB->GetParent()->GetTransform();

  const std::vector<glm::vec2>& axisA = meshA.GetAxis();
  const std::vector<glm::vec2>& axisB = meshB.GetAxis();

  float overlap = std::numeric_limits<float>::max();
  glm::vec2 smallestAxis;

  //sat can return right when an axis is found that it doesnt collide on.

  //in preperation for a collision
  //CollisionOccurence collisionOccurence(true);

  //cehcks the first objects axis to inspect collisoin status.
  CollisionOccurence::CollisionStatus collisionStatus = PerformAxisProjection(axisA, meshA, meshB, overlap, smallestAxis);

  if (collisionStatus == CollisionOccurence::CollisionStatus::COLLIDING)
  {
    //checks all object b axis if a collision still has not been detected
    collisionStatus = PerformAxisProjection(axisB, meshA, meshB, overlap, smallestAxis);
  }

  //if overlap is small enough consider them touching
  if (overlap < 0.01f)
  {
    collisionStatus = CollisionOccurence::CollisionStatus::TOUCHING;
  }
  
  //sets the objects
  collOcc.objectA_ = objectA->GetComponent<RigidBodyComponent>();
  collOcc.objectB_ = objectB->GetComponent<RigidBodyComponent>();
  collOcc.penetration_ = overlap;
  collOcc.collisionNormal_ = smallestAxis;
  collOcc.restitution_ = std::min(collOcc.objectA_->bounce_, collOcc.objectB_->bounce_);

  //then give it the status of that collision and return;
  collOcc.collisionStatus_ = collisionStatus;

  collOcc.objectA_->UpdateCollisionWith(collOcc.objectB_, collisionStatus);
  collOcc.objectB_->UpdateCollisionWith(collOcc.objectA_, collisionStatus);
}

CollisionOccurence::CollisionStatus PolygonalCollisionProfile::PerformAxisProjection(const std::vector<glm::vec2>& axisA, Mesh &meshA, Mesh &meshB, float &overlap, glm::vec2 &smallestAxis) const
{
  for (const glm::vec2& line : axisA)
  {
    Mesh::Projection meshAProjected;
    Mesh::Projection meshBProjected;
    meshA.Project(line, meshAProjected);
    meshB.Project(line, meshBProjected);

    //returns collision status
    CollisionOccurence::CollisionStatus collStatus = meshAProjected.IsOverlapping(meshBProjected);

    //std::cout << int(collStatus) << std::endl;

    if (collStatus == CollisionOccurence::CollisionStatus::NOT_COLLIDING || collStatus == CollisionOccurence::CollisionStatus::TOUCHING)
    {
      return collStatus;
    }
    else if (collStatus == CollisionOccurence::CollisionStatus::COLLIDING)
    {
      float o = meshAProjected.GetOverlap(meshBProjected);

      if (o < overlap)
      {
        overlap = o;
        smallestAxis = line;
      }
    }
  }

  return CollisionOccurence::CollisionStatus::COLLIDING;
}

CollisionProfile::CollisionProfile()
{
}

CollisionComponent* CollisionProfile::GetCollisionComponent()
{
  return collisionComponent_;
}

void CollisionProfile::SetCollisionComponent(CollisionComponent* thisCollider)
{
  collisionComponent_ = thisCollider;
}

