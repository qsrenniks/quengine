#include "stdafx.h"
#include "CollisionComponent.h"
#include "GameObjectSystem.h"
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

CollisionOccurence::CollisionStatus CollisionComponent::IsCollidingWith(CollisionComponent* otherCollider) const
{
  return collisionProfile_->IsProfileCollidingWith(otherCollider->collisionProfile_);
}

//CollisionComponent::CollisionInformation CollisionComponent::RetrieveCollisionInformation(CollisionComponent* collComp)
//{
//  if (!isOverlappingWithSomething_)
//  {
//    return CollisionInformation();
//  }
//  
//  if (std::find(overlappingColliders_.cbegin(), overlappingColliders_.cend(), collComp) == overlappingColliders_.cend())
//  {
//    //something weird has happened
//    assert(false);
//  }
//
//  CollisionInformation collInfo;
//
//  PhysicsComponent* otherPhys = collComp->GetParent()->GetComponent<PhysicsComponent>();
//
//  if (otherPhys != nullptr)
//  {
//    collInfo.rotationalVelocity = otherPhys->GetRotationalVelocity();
//    collInfo.velocity = otherPhys->GetVelocity();
//    collInfo.isOtherStatic = otherPhys->GetIsStatic();
//  }
//  else
//  {
//    collInfo.isOtherStatic = true;
//  }
//  
//  collInfo.isValid = true;
//  return collInfo;
//}

//only called when a collision has occurred
void CollisionComponent::Inform(CollisionComponent* collidingOther)
{
  //if it does not find this collider already in the lsit then add it 
  //if (std::find(overlappingColliders_.cbegin(), overlappingColliders_.cend(), collidingOther) == overlappingColliders_.cend())
  //{
  //  isOverlappingWithSomething_ = true;
  //  overlappingColliders_.push_back(collidingOther);
  //  onEnterOverlap_.Broadcast(collidingOther);
  //}

  if (overlappingCollider_ == nullptr && isOverlappingWithSomething_ == false)
  {
    isOverlappingWithSomething_ = true;
    overlappingCollider_ = collidingOther;
    onEnterOverlap_.Broadcast(collidingOther);
  }


}

void CollisionComponent::Reset(CollisionComponent* notCollidingOther)
{
  //it was previously colliding with something 
  //if (isOverlappingWithSomething_ == true && std::find(overlappingColliders_.cbegin(), overlappingColliders_.cend(), notCollidingOther) != overlappingColliders_.cend())
  //{
  //  onExitOverlap_.Broadcast(notCollidingOther);
  //  overlappingColliders_.remove(notCollidingOther);
  //}

  //if (overlappingColliders_.empty() == true)
  //{
  //  isOverlappingWithSomething_ = false;
  //  collisionOccurence_.SetValid(false);
  //}

  if (notCollidingOther == overlappingCollider_ && isOverlappingWithSomething_ == true)
  {
    isOverlappingWithSomething_ = false;
    onExitOverlap_.Broadcast(notCollidingOther);
    overlappingCollider_ = nullptr;
    collisionOccurence_.SetValid(false);
  }

}

//void CollisionComponent::SetMTV(const glm::vec2& mtv)
//{
//  mtv_ = mtv;
//}

//const glm::vec2& CollisionComponent::GetMTV() const
//{
//  return mtv_;
//}

bool CollisionComponent::IsOverlapping()
{
  return isOverlappingWithSomething_;
}

CollisionComponent* CollisionComponent::GetOverlappingCollider()
{
  return overlappingCollider_;
}

void CollisionComponent::SetCollisionOccurence(CollisionOccurence newCollisionOccurence)
{
  collisionOccurence_ = newCollisionOccurence;
}

CollisionOccurence& CollisionComponent::GetCollisionOccurence()
{
  return collisionOccurence_;
}

SquareCollisionProfile::SquareCollisionProfile(CollisionComponent*& component)
  : CollisionProfile(component)
{
  
}

CollisionOccurence::CollisionStatus SquareCollisionProfile::IsProfileCollidingWith(CollisionProfile* otherProfile) const
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
  CollisionOccurence::CollisionStatus aAxisStatus = PerformAxisProjection(axisA, meshA, meshB, overlap, smallestAxis);
  if (aAxisStatus == CollisionOccurence::CollisionStatus::NOT_COLLIDING || aAxisStatus == CollisionOccurence::CollisionStatus::TOUCHING)
  {
    return aAxisStatus;
  }

  //checks all object b axis if a collision still has not been detected
  CollisionOccurence::CollisionStatus bAxisStatus = PerformAxisProjection(axisB, meshA, meshB, overlap, smallestAxis);
  if (bAxisStatus == CollisionOccurence::CollisionStatus::NOT_COLLIDING || aAxisStatus == CollisionOccurence::CollisionStatus::TOUCHING)
  {
    return bAxisStatus;
  }

  CollisionOccurence collisionOccurenceA(true);
  CollisionOccurence collisionOccurenceB(true);

  glm::vec2 mtv = smallestAxis * overlap;
  //send resolve here
  //collisionComponent_->SetMTV(mtv);
  collisionOccurenceA.collisionStatus_ = aAxisStatus;
  collisionOccurenceA.mtv_ = mtv;
  collisionComponent_->SetCollisionOccurence(collisionOccurenceA);

  //otherProfile->GetCollisionComponent()->SetMTV(mtv);
  collisionOccurenceB.collisionStatus_ = bAxisStatus;
  collisionOccurenceB.mtv_ = mtv;
  otherProfile->GetCollisionComponent()->SetCollisionOccurence(collisionOccurenceB);

  return CollisionOccurence::CollisionStatus::COLLIDING;
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

