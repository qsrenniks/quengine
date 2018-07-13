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

void GameObjectSystem::CreateObjectRandomly()
{
  TileGameObject* gameObject = SpawnGameObject<TileGameObject>();

  static std::default_random_engine generator;
  std::normal_distribution<float> dist(0.0f, 0.5f);

  float randX = dist(generator);

  gameObject->GetTransform().SetPosition(glm::vec2(randX, 0.5f));
}

void GameObjectSystem::UpdateCollision()
{
  for (CollisionList::iterator itr = activeCollisionGameObjects_.begin(); itr != activeCollisionGameObjects_.end(); itr++)
  {
    if ((*itr)->GetIsDisabled() == true)
    {
      continue;
    }

    for (CollisionList::iterator otherItr = itr; otherItr != activeCollisionGameObjects_.end(); otherItr++)
    {
      if (itr == otherItr || (*otherItr)->GetIsDisabled() == true)
      {
        continue; 
      }

      //collision check
      if ((*itr)->IsCollidingWith(*otherItr))
      {
        //tell both colliders that they are colliding
        (*itr)->Inform(*otherItr);
        (*otherItr)->Inform(*itr);
      }
      else
      {
        (*itr)->Reset(*otherItr);
        (*otherItr)->Reset(*itr);
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

void GameObjectSystem::Load()
{
  //AddGameObject(new TileGameObject());
  //SpawnGameObject<TileGameObject>()->GetTransform().SetPosition(glm::vec2(0.25f, 0.25f));
  //SpawnGameObject<TileGameObject>()->GetTransform().SetPosition(glm::vec2(0.0f, 0.0f));
  //SpawnGameObject<TileGameObject>()->GetTransform().SetPosition(glm::vec2(-0.25f, -0.25f));
  //AddGameObject(new DebugGameObject());
  SpawnGameObject<DebugGameObject>();
}

static float timer = 0.0f;
static float every = 0.2f;
void GameObjectSystem::Update(float dt)
{
  //spawn game objects
  timer += dt;
  if (timer >= every)
  {
    CreateObjectRandomly();
    timer -= every;
  }

  auto DestroyGameObjectLambda = [&](auto i) { DestroyGameObject(i); };
  auto UpdateGameObjectLambda = [&](auto i) { i->UpdateGameObject(dt); };

  std::for_each(gameObjectRegistry_.begin(), gameObjectRegistry_.end(), DestroyGameObjectLambda);

  UpdateCollision();

  std::for_each(gameObjectRegistry_.begin(), gameObjectRegistry_.end(), UpdateGameObjectLambda);



}

void GameObjectSystem::Unload()
{

}