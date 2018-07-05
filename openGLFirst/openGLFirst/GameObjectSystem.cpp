#include "stdafx.h"
#include "GameObjectSystem.h"
#include "IGameObject.h"
#include <algorithm>

//all game objects
#include "DebugGameObject.h"
#include "TileGameObject.h"
#include "CollisionComponent.h"
#include <iostream>

struct CollisionUpdater
{


  CollisionUpdater(GameObjectSystem::CollisionList& collisionList)
    : collisionList_(collisionList)
  {}

  void operator()(CollisionComponent* collisionComponent)
  {
    if (collisionList_.empty())
    {
      return;
    }

    for (auto otherCollider : collisionList_)
    {
      if (collisionComponent == otherCollider)
      {
        continue;
      }

      if (collisionComponent->IsCollidingWith(otherCollider))
      {
        std::cout << "Objects Colliding!" << std::endl;
      }
    }
  }

  GameObjectSystem::CollisionList& collisionList_;
};

void GameObjectSystem::AddGameObject(IGameObject* gameObject)
{
  gameObjectRegistry_.push_back(gameObject);
}

void GameObjectSystem::AddCollisionComponent(CollisionComponent* collisionComponent)
{
  collisionGameObjects_.push_back(collisionComponent);
}

void GameObjectSystem::DestroyGameObject(IGameObject*& gameObject)
{
  if (gameObject->IsMarkedForDestroy())
  {
    gameObjectRegistry_.remove(gameObject);
    delete gameObject;
    gameObject = nullptr;
  }
}

void GameObjectSystem::RemoveCollisonComponent(CollisionComponent* collisionComponent)
{
  collisionGameObjects_.remove(collisionComponent);
}

GameObjectSystem::~GameObjectSystem()
{
  for (auto gameObjects : gameObjectRegistry_)
  {
    delete gameObjects;
  }

  for (auto collisionGameObjects : collisionGameObjects_)
  {
    delete collisionGameObjects;
  }
}

void GameObjectSystem::LoadSystem()
{
  AddGameObject(new TileGameObject());
  AddGameObject(new DebugGameObject());
}

void GameObjectSystem::UpdateSystem(float dt)
{
  auto DestroyGameObjectLambda = [&](IGameObject* i) { DestroyGameObject(i); };
  auto UpdateGameObjectLambda = [&](IGameObject* i) { i->UpdateGameObject(dt); };

  std::for_each(gameObjectRegistry_.begin(), gameObjectRegistry_.end(), DestroyGameObjectLambda);

  std::for_each(collisionGameObjects_.begin(), collisionGameObjects_.end(), CollisionUpdater(collisionGameObjects_));

  std::for_each(gameObjectRegistry_.begin(), gameObjectRegistry_.end(), UpdateGameObjectLambda);

}

void GameObjectSystem::UnloadSystem()
{

}