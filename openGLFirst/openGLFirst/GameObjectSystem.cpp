#include "stdafx.h"
#include "GameObjectSystem.h"
#include "IGameObject.h"
#include <algorithm>

//all game objects
#include "DebugGameObject.h"
#include "TileGameObject.h"
#include "CollisionComponent.h"
#include <iostream>

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

void GameObjectSystem::UpdateCollision()
{
  for (CollisionList::iterator itr = collisionGameObjects_.begin(); itr != collisionGameObjects_.end(); itr++)
  {
    for (CollisionList::iterator otherItr = itr; otherItr != collisionGameObjects_.end(); otherItr++)
    {
      if (itr == otherItr)
      {
        continue;
      }

      if ((*itr)->IsCollidingWith(*otherItr))
      {
        std::cout << "Objects are colliding!";
      }
    }
  }
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

  UpdateCollision();

  std::for_each(gameObjectRegistry_.begin(), gameObjectRegistry_.end(), UpdateGameObjectLambda);

}

void GameObjectSystem::UnloadSystem()
{

}