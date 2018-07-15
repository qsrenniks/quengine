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
      if (collComp->IsCollidingWith(otherComp))
      {
        //tell both colliders that they are colliding
        

        collComp->Inform(otherComp);
        collComp->onUpdateOverlap_.Broadcast(collComp->GetOverlappingColliders());

        otherComp->Inform(collComp);
        otherComp->onUpdateOverlap_.Broadcast(otherComp->GetOverlappingColliders());
      }
      else
      {
        collComp->Reset(otherComp);
        otherComp->Reset(collComp);
      }
    }
  }
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
  SpawnGameObject<TileGameObject>()->GetTransform().SetPosition(glm::vec2(0.5f, -0.25f));
  SpawnGameObject<TileGameObject>()->GetTransform().SetPosition(glm::vec2(0.5f, 0.25f));
  SpawnGameObject<TileGameObject>()->GetTransform().SetPosition(glm::vec2(0.0f, -0.25f));
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

  auto DrawGameObjectLambda = [&](IGameObject* i) { i->GetDrawList().Broadcast(); };
  std::for_each(gameObjectRegistry_.cbegin(), gameObjectRegistry_.cend(), DrawGameObjectLambda);


}

void GameObjectSystem::Unload()
{

}