#include "stdafx.h"
#include "CollisionComponent.h"
//#include "GameObjectSystem.h"
#include "Engine.h"
//#include "IGameObject.h"
#include "SpriteComponent.h"
#include <iostream>
#include <algorithm>
#include "PhysicsComponent.h"

CollisionComponent::CollisionComponent(CollisionProfile* profile/*= nullptr*/)
  : collisionProfile_(profile)
{

}

CollisionComponent::~CollisionComponent()
{
  GameObjectSystem* sys = Engine::Instance()->GetGameObjectSystem();
  sys->RemoveCollisonComponent(this);

  delete collisionProfile_;
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

void CollisionComponent::Parent(IGameObject* parent)
{
  IComponent::Parent(parent);

  GameObjectSystem* sys = Engine::Instance()->GetGameObjectSystem();
  sys->AddCollisionComponent(this);
}

void CollisionComponent::Register()
{
  IGameObject* parent = GetParent();

  //i am not registering update function since collision component is updated differently.
  parent->GetDrawList().AddFunction(this, &CollisionComponent::Draw);
  parent->GetComponentUpdateList().AddFunction(this, &CollisionComponent::Update);
}

void CollisionComponent::IsCollidingWith(CollisionComponent* otherCollider) const
{
  collisionProfile_->IsProfileCollidingWith(otherCollider->collisionProfile_);
}

//only called when a collision has occurred
//void CollisionComponent::Inform(CollisionComponent* collidingOther)
//{
//  if (overlappingCollider_ == nullptr && isOverlappingWithSomething_ == false)
//  {
//    isOverlappingWithSomething_ = true;
//    overlappingCollider_ = collidingOther;
//    onEnterOverlap_.Broadcast(collidingOther);
//  }
//}

//void CollisionComponent::Reset(CollisionComponent* notCollidingOther)
//{
//  if (notCollidingOther == overlappingCollider_ && isOverlappingWithSomething_ == true)
//  {
//    isOverlappingWithSomething_ = false;
//    onExitOverlap_.Broadcast(notCollidingOther);
//    overlappingCollider_ = nullptr;
//    collisionOccurence_.SetValid(false);
//  }
//}

//bool CollisionComponent::IsOverlapping()
//{
  //return isOverlappingWithSomething_;
//}

CollisionComponent* CollisionComponent::GetOverlappingCollider()
{
  return overlappingCollider_;
}

//void CollisionComponent::SetCollisionOccurence(CollisionOccurence newCollisionOccurence)
//{
//  collisionOccurence_ = newCollisionOccurence;
//}

//CollisionOccurence& CollisionComponent::GetCollisionOccurence()
//{
//  return collisionOccurence_;
//}

SquareCollisionProfile::SquareCollisionProfile(CollisionComponent*& component)
  : CollisionProfile(component)
{
  
}

void SquareCollisionProfile::IsProfileCollidingWith(CollisionProfile* otherProfile) const
{
  SpriteComponent* spriteA = collisionComponent_->GetParent()->GetComponent<SpriteComponent>();
  SpriteComponent* spriteB = otherProfile->GetCollisionComponent()->GetParent()->GetComponent<SpriteComponent>();

  //get meshes
  Mesh& meshA = spriteA->GetMesh();
  Mesh& meshB = spriteB->GetMesh();

  Transform& transformA = spriteA->GetParent()->GetTransform();
  Transform& transformB = spriteB->GetParent()->GetTransform();

  std::vector<glm::vec2> axisA;
  std::vector<glm::vec2> axisB;

  meshA.GetAxis(axisA, transformA.BuildTransform());
  meshB.GetAxis(axisB, transformB.BuildTransform());

  float overlap = std::numeric_limits<float>::max();
  glm::vec2 smallestAxis;

  //cehcks the first objects axis to inspect collisoin status.
  CollisionOccurence::CollisionStatus collisionStatus = PerformAxisProjection(axisA, meshA, meshB, overlap, smallestAxis);

  if (collisionStatus == CollisionOccurence::CollisionStatus::NOT_COLLIDING || collisionStatus == CollisionOccurence::CollisionStatus::TOUCHING)
  {
    return;
  }

  //checks all object b axis if a collision still has not been detected
  collisionStatus = PerformAxisProjection(axisB, meshA, meshB, overlap, smallestAxis);

  if (collisionStatus == CollisionOccurence::CollisionStatus::NOT_COLLIDING || collisionStatus == CollisionOccurence::CollisionStatus::TOUCHING)
  {
    return;
  }

  //
  // this next step essentially fills an instance of collision occurence with information about the collision and then passes that on to the gameobjecst
  // involved with the collision.
  //

  //creating the collision occurence objects to then be passed to the objecst that were involved with a collision to then be resolved.
  glm::vec2 mtv = smallestAxis * overlap;

  CollisionOccurence collisionOccurence(true);
  collisionOccurence.mtv_ = mtv;

  collisionOccurence.collisionStatus_ = collisionStatus;

  collisionOccurence.objectA_ = collisionComponent_;
  //collisionOccurence.objectACollisionStatus_ = aAxisStatus;
  collisionOccurence.objectB_ = otherProfile->GetCollisionComponent();
  //collisionOccurence.objectBCollisionStatus_ = bAxisStatus;

  collisionOccurence.objectAsVelocity_ = transformA.GetInstantVelocity();
  collisionOccurence.objectBsVelocity_ = transformB.GetInstantVelocity();

  //std::cout << "mtv: " << mtv.x << ": " << mtv.y << std::endl;


  Engine::Instance()->GetGameObjectSystem()->AddCollisionOccurence(collisionOccurence);
}

CollisionOccurence::CollisionStatus SquareCollisionProfile::PerformAxisProjection(std::vector<glm::vec2>& axisA, Mesh &meshA, Mesh &meshB, float &overlap, glm::vec2 &smallestAxis) const
{
  for (glm::vec2& line : axisA)
  {
    line = glm::normalize(line);

    Mesh::Projection meshAProjected = meshA.project(line);
    Mesh::Projection meshBProjected = meshB.project(line);

    //returns collision status
    CollisionOccurence::CollisionStatus collStatus = meshAProjected.IsOverlapping(meshBProjected);

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

CollisionProfile::CollisionProfile(CollisionComponent*& component)
  : collisionComponent_(component)
{
}

CollisionComponent* CollisionProfile::GetCollisionComponent()
{
  return collisionComponent_;
}

