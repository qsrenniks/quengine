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
#include "CollisionOccurence.h"
#include "RigidBodyGameObject.h"

void GameObjectSystem::AddCollisionOccurence(const CollisionOccurence& occurence)
{
  collisionOccurences_.push_back(occurence);
}

void GameObjectSystem::AddGameObject(IGameObject* gameObject)
{
  gameObjectRegistry_.push_back(gameObject);
}

void GameObjectSystem::AddRigidBodyGameObject(RigidBodyGameObject* object)
{
  collisionGameObjects_.push_back(object);
}

void GameObjectSystem::DestroyGameObject(IGameObject*& gameObjectToDestroy)
{
  if (gameObjectToDestroy->IsMarkedForDestroy())
  {
    gameObjectRegistry_.remove(gameObjectToDestroy);
    gameObjectToDestroy = nullptr;
  }
}

void GameObjectSystem::RemoveCollisonComponent(RigidBodyGameObject* collisionComponent)
{
  collisionGameObjects_.remove(collisionComponent);
}

void GameObjectSystem::CalculateAndResolveCollisions()
{
  const static int iterations = 4;
  for (int i = 0; i < iterations; i++)
  {
    CalculateCollisions();
    //ResolveCollisions();
  }
}

void GameObjectSystem::CalculateCollisions()
{
  for (CollisionList::const_iterator itr = collisionGameObjects_.cbegin(); itr != collisionGameObjects_.cend(); itr++)
  {
    for (CollisionList::const_iterator otherItr = itr; otherItr != collisionGameObjects_.cend(); otherItr++)
    {
      RigidBodyGameObject* objectA = *itr;
      RigidBodyGameObject* objectB = *otherItr;

      if (itr == otherItr)
      {
        continue; 
      }

      //collision check
      CollisionOccurence occ(true);
      objectA->CheckCollisionAgainst(objectB, occ);

      //this responds to collisions as they come in

      if (occ.IsValid() && occ.collisionStatus_ == CollisionOccurence::CollisionStatus::COLLIDING)
      {
        PhysicsComponent::RespondToPhysicalCollision(occ);
        //AddCollisionOccurence(occ);
      }
    }
  }
}

void GameObjectSystem::ResolveCollisions()
{
  if (collisionOccurences_.empty() == true)
  {
    return;
  }

  auto collisionResolutionLambda = [&](CollisionOccurence& occurence)
  {

    //doing this lets both objects resolve the collision in their own ways.
    //you use - occurence so that the mtv can get negated in order to push the objects away from each other.
    //if they were both responding using the same mtv they would both move in the same direction causing some interesting collision problems

    PhysicsComponent::RespondToPhysicalCollision(occurence);

    occurence.isResolved_ = true;
  };

  std::for_each(collisionOccurences_.begin(), collisionOccurences_.end(), collisionResolutionLambda);

  auto isResolved = [&](CollisionOccurence collOcc) -> bool { return collOcc.isResolved_; };
  collisionOccurences_.remove_if(isResolved);
}

GameObjectSystem::GameObjectSystem()
{

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
  SpawnGameObject<TileGameObject>()->GetTransform().SetPosition(glm::vec2(0.5f, 0.0f)); //right
  //SpawnGameObject<TileGameObject>()->GetTransform().SetPosition(glm::vec2(0.0f, 0.5f)); //up
  SpawnGameObject<TileGameObject>()->GetTransform().SetPosition(glm::vec2(-0.5f, 0.0f));  //left
  SpawnGameObject<TileGameObject>()->GetTransform().SetPosition(glm::vec2(0.0f, -0.5f));//down
  SpawnGameObject<DebugGameObject>();
  
  //Double bounce problem
  //SpawnGameObject<PhysicsBodyGameObject>()->GetTransform().SetPosition(glm::vec2(-0.055f, -0.25f));
  //SpawnGameObject<PhysicsBodyGameObject>()->GetTransform().SetPosition(glm::vec2(0.055f, -0.25f));

  SpawnGameObject<PhysicsBodyGameObject>()->GetTransform().SetPosition(glm::vec2(0.0f, 0.0f));
  SpawnGameObject<PhysicsBodyGameObject>()->GetTransform().SetPosition(glm::vec2(0.0f, 0.1f));
  SpawnGameObject<PhysicsBodyGameObject>()->GetTransform().SetPosition(glm::vec2(0.0f, 0.0f));
  SpawnGameObject<PhysicsBodyGameObject>()->GetTransform().SetPosition(glm::vec2(0.0f, 0.0f));
 
}

void GameObjectSystem::Update(float dt)
{
  auto DestroyGameObjectLambda = [&](auto i) { DestroyGameObject(i); };
  std::for_each(gameObjectRegistry_.cbegin(), gameObjectRegistry_.cend(), DestroyGameObjectLambda);

  auto UpdateGameObjectLambda = [&](auto i) { i->UpdateGameObject(dt); };
  std::for_each(gameObjectRegistry_.cbegin(), gameObjectRegistry_.cend(), UpdateGameObjectLambda);
  
  CalculateAndResolveCollisions();
  
  auto DrawGameObjectLambda = [&](IGameObject* i) { i->GetDrawList().Broadcast(); };
  std::for_each(gameObjectRegistry_.cbegin(), gameObjectRegistry_.cend(), DrawGameObjectLambda);
}

void GameObjectSystem::Unload()
{

}
