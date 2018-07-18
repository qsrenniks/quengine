#include "stdafx.h"
#include "CollisionResolution.h"
#include "Transform.h"
#include "CollisionOccurence.h"
#include "CollisionComponent.h"
#include "PhysicsComponent.h"
//#include "TileGameObject.h"
//#include "DebugGameObject.h"
#include "TextLibrary.h"

void TileGameObjectANDDebugGameObject(const CollisionOccurence& occurence);
void PhysicsBodyGameObjectANDDebugGameObject(const CollisionOccurence& occurence);

CollisionResolution::CollisionResolution()
{
  using namespace TextLibrary;

  collisionMap_[std::make_pair(GameObjectNames::TileGameObject, GameObjectNames::DebugGameObject)] = TileGameObjectANDDebugGameObject;
  collisionMap_[std::make_pair(GameObjectNames::DebugGameObject, GameObjectNames::TileGameObject)] = TileGameObjectANDDebugGameObject;

  collisionMap_[std::make_pair(GameObjectNames::DebugGameObject, GameObjectNames::PhysicsBodyGameObject)] = PhysicsBodyGameObjectANDDebugGameObject;
  collisionMap_[std::make_pair(GameObjectNames::PhysicsBodyGameObject, GameObjectNames::DebugGameObject)] = PhysicsBodyGameObjectANDDebugGameObject;
}

CollisionResolution::~CollisionResolution()
{
}

//
// all static collisoin responses go here.
//

void TileGameObjectANDDebugGameObject(const CollisionOccurence& occurence)
{
  //basic mtv move;
  //moves debug game object away from tile game object
  Transform& transformB = occurence.objectB_->GetParent()->GetTransform();

  glm::vec2 oldPosition = transformB.GetPosition();

  transformB.SetPosition(oldPosition + occurence.mtv_);
}

void PhysicsBodyGameObjectANDDebugGameObject(const CollisionOccurence& occurence)
{
  //handle physics collision
}

void CollisionResolution::DetermineResolution(const CollisionOccurence& occurence)
{
  ObjectPair occurencePair = std::make_pair(occurence.objectA_->GetParent()->GetObjectName(), occurence.objectB_->GetParent()->GetObjectName());
  //collisionMap_.at(occurencePair);
  //calls the function reference at occurence pair
  (collisionMap_[occurencePair])(occurence);
}

//
//void CollisionResponse::Respond(const CollisionOccurence& occurence)
//{
//  CollisionComponent *thisCollider = GetCollisionComponent();
//
//  Transform& thisTransform = thisCollider->GetParent()->GetTransform();
//
//  glm::vec2 thisPosition = thisTransform.GetPosition();
//
//  //we use half since the other half is gonna be used by the other collision
//  //since this will be negated for the other occurence you just add like normal
//  thisPosition += occurence.mtv_;
//
//  thisTransform.SetPosition(thisPosition);
//}
//
//void CollisionResponse::SetCollisionComponent(CollisionComponent* collisionComponent)
//{
//  collisionComponent_ = collisionComponent;
//}
//
//CollisionComponent* CollisionResponse::GetCollisionComponent() const
//{
//  return collisionComponent_;
//}
//
//PhysicalResponse::PhysicalResponse(PhysicsComponent* physicsComponent, bool isStatic, float mass, float friction, float bounce)
//  : physicsComponent_(physicsComponent)
//  , mass_(mass)
//  , friction_(friction)
//  , bounce_(bounce)
//  , isStatic_(isStatic)
//{
//}
//
//PhysicalResponse::~PhysicalResponse()
//{
//
//}
//
//void PhysicalResponse::Respond(const CollisionOccurence& occurence)
//{
//  if (isStatic_ == true)
//  {
//    return;
//  }
//
//  //given mtv
//  //given physics component
//  //given mass and bounce determine what the velocity should be after a collision
//
//  //perform the usual response and then do a physical calculation to change the objects velocity
//  CollisionResponse::Respond(occurence);
//
//  float mass = mass_;
//  float friction = friction_;
//  float bounce = bounce_;
//
//  glm::vec2 oldVelocity = physicsComponent_->GetVelocity();
//
//  glm::vec2 normMtv;
//  if (occurence.mtv_.x == 0.0f && occurence.mtv_.y == 0.0f)
//  {
//    normMtv = glm::vec2(0);
//  }
//  else
//  {
//    normMtv = glm::normalize(occurence.mtv_);
//  }
//
//  glm::vec2 normVelo;
//
//  if (oldVelocity.x == 0.0f && oldVelocity.y == 0.0f)
//  {
//    normVelo = glm::vec2(0.0f);
//  }
//  else
//  {
//    normVelo = glm::normalize(oldVelocity);
//  }
//
//  glm::vec2 s = normMtv * glm::length(oldVelocity);
//  float dotp = glm::dot(normMtv, normVelo);
//
//  dotp = glm::abs(dotp);
//
//  s *= dotp;
//
//  glm::vec2 newVelocity = ((oldVelocity + s) * friction) + (s * bounce);
//
//  physicsComponent_->SetVelocity(newVelocity);
//}
//
//void DebugResponse::Respond(const CollisionOccurence& occurence)
//{
//  //Debug response does nothing.
//}
