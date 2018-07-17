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
  //SpawnGameObject<TileGameObject>()->GetTransform().SetPosition(glm::vec2(0.5f, 0.25f)); //right
  //SpawnGameObject<TileGameObject>()->GetTransform().SetPosition(glm::vec2(0.0f, 0.75f)); //up
  //SpawnGameObject<TileGameObject>()->GetTransform().SetPosition(glm::vec2(-0.5f, 0.25f));  //left
  SpawnGameObject<TileGameObject>()->GetTransform().SetPosition(glm::vec2(0.0f, -0.25f));//down
  //SpawnGameObject<PhysicsBodyGameObject>()->GetTransform().SetPosition(glm::vec2(0.0f, 0.5f));

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
