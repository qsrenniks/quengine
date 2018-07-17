#include "stdafx.h"
#include "GameObjectSystem.h"
#include "IGameObject.h"
#include <algorithm>

//all game objects
#include "DebugGameObject.h"
#include "TileGameObject.h"
#include "PhysicsComponent.h"
#include "CollisionComponent.h"
#include <iostream>
//
// test
//
#include "Engine.h"
#include "InputSystem.h"
#include <stdlib.h>
#include <string>
#include <random>
#include "PhysicsBodyGameObject.h"

void GameObjectSystem::AddCollisionOccurence(CollisionOccurence occurence)
{
  collisionOccurences_.push_back(occurence);
}

void GameObjectSystem::AddGameObject(IGameObject* gameObject)
{
  gameObjectRegistry_.push_back(gameObject);
}

void GameObjectSystem::AddCollisionComponent(CollisionComponent* collisionComponent)
{
  collisionGameObjects_.push_back(collisionComponent);
}

void GameObjectSystem::DestroyGameObject(IGameObject*& gameObjectToDestroy)
{
  if (gameObjectToDestroy->IsMarkedForDestroy())
  {
    gameObjectRegistry_.remove(gameObjectToDestroy);
    gameObjectToDestroy = nullptr;
  }
}

void GameObjectSystem::RemoveCollisonComponent(CollisionComponent* collisionComponent)
{
  collisionGameObjects_.remove(collisionComponent);
}

//void GameObjectSystem::CreateObjectRandomly()
//{
//  TileGameObject* gameObject = SpawnGameObject<TileGameObject>();
//
//  static std::default_random_engine generator;
//  std::uniform_real_distribution<float> dist(-0.5f, 0.5f);
//
//  float randX = dist(generator);
//
//  gameObject->GetTransform().SetPosition(glm::vec2(randX, 1.0f));
//}

void GameObjectSystem::CalculateCollisions()
{
  for (CollisionList::const_iterator itr = collisionGameObjects_.cbegin(); itr != collisionGameObjects_.cend(); itr++)
  {
    for (CollisionList::const_iterator otherItr = itr; otherItr != collisionGameObjects_.cend(); otherItr++)
    {
      CollisionComponent* collComp = *itr;
      CollisionComponent* otherComp = *otherItr;

      if (itr == otherItr /*|| otherComp->GetIsDisabled() == true*/)
      {
        continue; 
      }

      //collision check
      collComp->IsCollidingWith(otherComp);

    }
  }

  //RESOLVE COLLISIONS 
}

void GameObjectSystem::ResolveCollisions()
{

  
  if (collisionOccurences_.empty() == true)
  {
    return;
  }

  ///
  // DEFAULT COLLISION RESOLUTION LAMBDA
  ///

  auto collisionResolutionLambda = [&](CollisionOccurence& occurence)
  {

    //doing this lets both objects resolve the collision in their own ways.
    //you use - occurence so that the mtv can get negated in order to push the objects away from each other.
    //if they were both responding using the same mtv they would both move in the same direction causing some interesting collision problems
    occurence.objectA_->GetCollisionResponse()->Respond(-occurence);
    occurence.objectB_->GetCollisionResponse()->Respond(occurence);
    //resolve collision
    //Transform& bTransform = occurence.objectB_->GetParent()->GetTransform();
    //Transform& aTransform = occurence.objectA_->GetParent()->GetTransform();

    //glm::vec2 bPosition = bTransform.GetPosition();
    //glm::vec2 aPosition = aTransform.GetPosition();

    //glm::vec2 mtvHalf = occurence.mtv_ / 2.0f;

    //bPosition += mtvHalf;
    //aPosition -= mtvHalf;

    //bTransform.SetPosition(bPosition);
    //aTransform.SetPosition(aPosition);

    occurence.isResolved_ = true;
    //collisionOccurences_.remove(occurence);

  };
  std::for_each(collisionOccurences_.begin(), collisionOccurences_.end(), collisionResolutionLambda);

  auto isResolved = [&](CollisionOccurence collOcc) -> bool { return collOcc.isResolved_; };
  collisionOccurences_.remove_if(isResolved);
}

GameObjectSystem::~GameObjectSystem()
{
  for (auto& gameObjects : gameObjectRegistry_)
  {
    delete gameObjects;
    gameObjects = nullptr;
  }
}

void GameObjectSystem::Load()
{
  //SpawnGameObject<TileGameObject>()->GetTransform().SetPosition(glm::vec2(0.0f, -0.25f));
  //SpawnGameObject<TileGameObject>()->GetTransform().SetPosition(glm::vec2(0.5f, -0.25f));
  SpawnGameObject<TileGameObject>()->GetTransform().SetPosition(glm::vec2(0.5f, 0.25f)); //right
  SpawnGameObject<TileGameObject>()->GetTransform().SetPosition(glm::vec2(0.0f, 0.75f)); //up
  SpawnGameObject<TileGameObject>()->GetTransform().SetPosition(glm::vec2(-0.5f, 0.25f));  //left
  SpawnGameObject<TileGameObject>()->GetTransform().SetPosition(glm::vec2(0.0f, -0.25f));//down
  SpawnGameObject<PhysicsBodyGameObject>()->GetTransform().SetPosition(glm::vec2(0.0f, 0.5f));
  //SpawnGameObject<PhysicsBodyGameObject>()->GetTransform().SetPosition(glm::vec2(0.2f, 0.5f));
  //SpawnGameObject<PhysicsBodyGameObject>()->GetTransform().SetPosition(glm::vec2(-0.2f, 0.5f));

  //SpawnGameObject<TileGameObject>()->GetTransform().SetPosition(glm::vec2(-0.25f, -0.25f));
  SpawnGameObject<DebugGameObject>();
}

void GameObjectSystem::Update(float dt)
{

  auto DestroyGameObjectLambda = [&](auto i) { DestroyGameObject(i); };
  std::for_each(gameObjectRegistry_.cbegin(), gameObjectRegistry_.cend(), DestroyGameObjectLambda);

  auto UpdateGameObjectLambda = [&](auto i) { i->UpdateGameObject(dt); };
  std::for_each(gameObjectRegistry_.cbegin(), gameObjectRegistry_.cend(), UpdateGameObjectLambda);
  
  CalculateCollisions();

  ResolveCollisions();

  auto DrawGameObjectLambda = [&](IGameObject* i) { i->GetDrawList().Broadcast(); };
  std::for_each(gameObjectRegistry_.cbegin(), gameObjectRegistry_.cend(), DrawGameObjectLambda);


}

void GameObjectSystem::Unload()
{

}

bool CollisionOccurence::operator==(CollisionOccurence otherCollision) const
{
  if (objectA_ == otherCollision.objectA_ && objectB_ == otherCollision.objectB_)
  {
    return true;
  }
  else return false;
}

void CollisionOccurence::ConstructNonCollisionOccurence(CollisionComponent* objectA, CollisionComponent* objectB, CollisionStatus collisionStatus)
{
  objectA_ = objectA;
  objectB_ = objectB;

  mtv_ = glm::vec2(0.0f, 0.0f);

  collisionStatus_ = collisionStatus;
}

CollisionOccurence CollisionOccurence::operator-()
{
  CollisionOccurence copy = *this;

  copy.mtv_ *= -1.0f;
  copy.halfMtv_ *= -1.0f;

  return copy;
}

void CollisionResponse::Respond(const CollisionOccurence& occurence)
{
  CollisionComponent *thisCollider = GetCollisionComponent();

  Transform& thisTransform = thisCollider->GetParent()->GetTransform();

  glm::vec2 thisPosition = thisTransform.GetPosition();

  //we use half since the other half is gonna be used by the other collision
  //since this will be negated for the other occurence you just add like normal
  thisPosition += occurence.mtv_;

  thisTransform.SetPosition(thisPosition);
}

void CollisionResponse::SetCollisionComponent(CollisionComponent* collisionComponent)
{
  collisionComponent_ = collisionComponent;
}

CollisionComponent* CollisionResponse::GetCollisionComponent() const
{
  return collisionComponent_;
}

PhysicalResponse::PhysicalResponse(PhysicsComponent* physicsComponent, bool isStatic, float mass, float friction, float bounce)
  : physicsComponent_(physicsComponent)
  , mass_(mass)
  , friction_(friction)
  , bounce_(bounce)
  , isStatic_(isStatic)
{
}

PhysicalResponse::~PhysicalResponse()
{

}

void PhysicalResponse::Respond(const CollisionOccurence& occurence)
{
  if (isStatic_ == true)
  {
    return;
  }

  //given mtv
  //given physics component
  //given mass and bounce determine what the velocity should be after a collision

  //perform the usual response and then do a physical calculation to change the objects velocity
  CollisionResponse::Respond(occurence);

  float mass = mass_;
  float friction = friction_;
  float bounce = bounce_;

  glm::vec2 oldVelocity = physicsComponent_->GetVelocity();

  glm::vec2 normMtv = glm::normalize(occurence.mtv_);
  
  glm::vec2 normVelo ;
  
  if (oldVelocity.x == 0.0f && oldVelocity.y == 0.0f)
  {
    normVelo = glm::vec2(0.0f);
  }
  else
  {
    normVelo = glm::normalize(oldVelocity);
  }

  glm::vec2 s = normMtv * glm::length(oldVelocity);
  float dotp = glm::dot(normMtv, normVelo);
  
  dotp = glm::abs(dotp);

  s *= dotp;


  glm::vec2 newVelocity = ((oldVelocity + s) * friction) + (s * bounce);

  physicsComponent_->SetVelocity(newVelocity);
}
