#include "stdafx.h"
#include "CollisionComponent.h"
//#include "GameObjectSystem.h"
#include "Engine.h"
//#include "IGameObject.h"
#include "SpriteComponent.h"
#include <iostream>
#include <algorithm>
#include "PhysicsComponent.h"

CollisionComponent::CollisionComponent(CollisionProfile* profile, CollisionResponse* collisionResponse)
  : collisionProfile_(profile)
  , collisionResponse_(collisionResponse)
{
  collisionProfile_->SetCollisionComponent(this);
  collisionResponse_->SetCollisionComponent(this);
}

CollisionComponent::~CollisionComponent()
{
  GameObjectSystem* sys = Engine::Instance()->GetGameObjectSystem();
  sys->RemoveCollisonComponent(this);

  delete collisionProfile_;
  delete collisionResponse_;
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

void CollisionComponent::InformOfCollision(CollisionOccurence collisionOccurence)
{
  // this function keeps track of collision state on the object.
  // this function is also responsible for calling the overlap event methods on the collision component
  // if the state coming in is different then the stored state then state has changed and updates should be made.

  if ((currentCollisionStatus_.collisionStatus_ == CollisionOccurence::CollisionStatus::COLLIDING || currentCollisionStatus_.collisionStatus_ == CollisionOccurence::CollisionStatus::TOUCHING)
      && collisionOccurence.collisionStatus_ == CollisionOccurence::CollisionStatus::NOT_COLLIDING)
  {
    onExitOverlap_.Broadcast(collisionOccurence);
  }
  else if ((currentCollisionStatus_.collisionStatus_ == CollisionOccurence::CollisionStatus::NOT_COLLIDING || currentCollisionStatus_.collisionStatus_ == CollisionOccurence::CollisionStatus::TOUCHING)
      && collisionOccurence.collisionStatus_ == CollisionOccurence::CollisionStatus::COLLIDING)
  {
    onEnterOverlap_.Broadcast(collisionOccurence);
  }
  //if they are both the same then state hasnt changed so broadcast the update delegate
  else if (currentCollisionStatus_.collisionStatus_ == CollisionOccurence::CollisionStatus::COLLIDING && collisionOccurence.collisionStatus_ == CollisionOccurence::CollisionStatus::COLLIDING)
  {
    onUpdateOverlap_.Broadcast(collisionOccurence);
  }

  currentCollisionStatus_ = collisionOccurence;
}

CollisionResponse* CollisionComponent::GetCollisionResponse()
{
  return collisionResponse_;
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

//CollisionComponent* CollisionComponent::GetOverlappingCollider()
//{
//  return overlappingCollider_;
//}

//void CollisionComponent::SetCollisionOccurence(CollisionOccurence newCollisionOccurence)
//{
//  collisionOccurence_ = newCollisionOccurence;
//}

//CollisionOccurence& CollisionComponent::GetCollisionOccurence()
//{
//  return collisionOccurence_;
//}

SquareCollisionProfile::SquareCollisionProfile()
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

  //in preperation for a collision
  CollisionOccurence collisionOccurence(true);

  //cehcks the first objects axis to inspect collisoin status.
  CollisionOccurence::CollisionStatus collisionStatus = PerformAxisProjection(axisA, meshA, meshB, overlap, smallestAxis);

  //checks all object b axis if a collision still has not been detected
  collisionStatus = PerformAxisProjection(axisB, meshA, meshB, overlap, smallestAxis);

  //if no collision occurred then it constructs the collision occurence in a different way and then passes it on to both game objects.
  if (collisionStatus == CollisionOccurence::CollisionStatus::NOT_COLLIDING || collisionStatus == CollisionOccurence::CollisionStatus::TOUCHING)
  {
    collisionOccurence.ConstructNonCollisionOccurence(collisionComponent_, otherProfile->GetCollisionComponent(), collisionStatus);
  } 
  else if (collisionStatus == CollisionOccurence::CollisionStatus::COLLIDING)
  {
    //this only falls through if a collision has occured

    //
    // this next step essentially fills an instance of collision occurence with information about the collision and then passes that on to the gameobjecst
    // involved with the collision.
    //
    //creating the collision occurence objects to then be passed to the objecst that were involved with a collision to then be resolved.
    glm::vec2 mtv = smallestAxis * overlap;

    //before the collision occurence is documented broadcast the events to both collision game objects.
    collisionOccurence.mtv_ = mtv;
    collisionOccurence.halfMtv_ = mtv / 2.0f;

    collisionOccurence.collisionStatus_ = collisionStatus;
    collisionOccurence.objectA_ = collisionComponent_;
    collisionOccurence.objectB_ = otherProfile->GetCollisionComponent();

    //TODO: the engine collision resolution system is only notified of a valid COLLISION occurence event. Maybe it should be notified about all? colliding or non-colliding
    Engine::Instance()->GetGameObjectSystem()->AddCollisionOccurence(collisionOccurence);
  }

  collisionComponent_->InformOfCollision(collisionOccurence);
  otherProfile->GetCollisionComponent()->InformOfCollision(collisionOccurence);
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

