#include "stdafx.h"
#include "GameObjectSystem.h"
#include "IGameObject.h"
#include <algorithm>

//all game objects
#include "DebugGameObject.h"
#include "TileGameObject.h"

void GameObjectSystem::AddGameObject(IGameObject *gameObject)
{
  gameObjectRegistry_.push_back(gameObject);
}

void GameObjectSystem::AddCollisionComponent(class CollisionComponent *collisionComponent)
{
  collisionGameObjects_.push_back(collisionComponent);
}

void GameObjectSystem::DestroyGameObject(IGameObject* gameObject)
{
  if (gameObject->IsMarkedForDestroy())
  {
    gameObjectRegistry_.remove(gameObject);
  }
}

void GameObjectSystem::RemoveCollisonComponent(class CollisionComponent *collisionComponent)
{
  collisionGameObjects_.remove(collisionComponent);
}

GameObjectSystem::~GameObjectSystem()
{
  for (IGameObject* a : gameObjectRegistry_)
  {
    delete a;
  }
}

void GameObjectSystem::LoadSystem()
{
  AddGameObject(new TileGameObject);
  AddGameObject(new DebugGameObject);
}

void GameObjectSystem::UpdateSystem(float dt)
{
  auto DestroyGameObjectLambda = [&](IGameObject *i) { DestroyGameObject(i); };
  auto UpdateGameObjectLambda = [&](IGameObject *i) { i->UpdateGameObject(dt); };

  std::for_each(gameObjectRegistry_.begin(), gameObjectRegistry_.end(), DestroyGameObjectLambda);
  std::for_each(gameObjectRegistry_.begin(), gameObjectRegistry_.end(), UpdateGameObjectLambda);


}

void GameObjectSystem::UnloadSystem()
{

}