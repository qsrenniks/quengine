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
#include "RigidBodyComponent.h"

void GameObjectSystem::AddCollisionOccurence(const CollisionOccurence& occurence)
{
  collisionOccurences_.push_back(occurence);
}

void GameObjectSystem::AddGameObject(std::unique_ptr<IGameObject>&& gameObject)
{
  //loop through list of game objects. is unique ptr is empty put it there. if it is not push it back
  //this could be a simple perf improvement
  gameObjectRegistry_.push_back(std::move(gameObject));

  //log to the game object system logger
  Engine::Instance()->GetLoggingSystem()->GetLogStream(GameObjectSystemLog) << "GameObjectSystem: Objects In System: " << gameObjectRegistry_.size() << std::endl;
}

void GameObjectSystem::RegisterRigidBodyComponent(RigidBodyComponent* object)
{
  rigidBodyComponentRegistry_.push_back(object);
}

void GameObjectSystem::DestroyGameObject(std::unique_ptr<IGameObject>& gameObjectToDestroy)
{
  if (gameObjectToDestroy->IsMarkedForDestroy())
  {
    gameObjectRegistry_.remove(gameObjectToDestroy);
  }
}

void GameObjectSystem::RemoveCollisonComponent(RigidBodyComponent* collisionComponent)
{
  rigidBodyComponentRegistry_.remove(collisionComponent);
}

void GameObjectSystem::OnMouseClick(glm::vec2 mousePos)
{
  SpawnGameObject<PhysicsBodyGameObject>()->GetTransform().SetPosition(mousePos);
}

void GameObjectSystem::CalculateAndResolveCollisions()
{
  CalculateCollisions();
  ResetBodies();
}

void GameObjectSystem::CalculateCollisions()
{
  for (CollisionList::const_iterator itr = rigidBodyComponentRegistry_.cbegin(); itr != rigidBodyComponentRegistry_.cend(); itr++)
  {
    for (CollisionList::const_iterator otherItr = itr; otherItr != rigidBodyComponentRegistry_.cend(); otherItr++)
    {
      RigidBodyComponent* objectA = *itr;
      RigidBodyComponent* objectB = *otherItr;

      if (itr == otherItr)
      {
        continue; 
      }

      //collision check
      CollisionOccurence occ;
      objectA->GetCollisionComponent()->IsCollidingWith(objectB->GetCollisionComponent(), occ);

      if (occ.collisionStatus_ == CollisionOccurence::CollisionStatus::COLLIDING)
      {
        occ.Resolve();
      }
    }
  }
}

void GameObjectSystem::ResetBodies()
{
  //auto lambda = [&](RigidBodyGameObject* object) 
  //{
  //  object->SetResolved(false);
  //};

  //std::for_each(collisionGameObjects_.begin(), collisionGameObjects_.end(), lambda);
}

std::string GameObjectSystem::GameObjectSystemLog = "GameObjectSystemLog";

GameObjectSystem::GameObjectSystem()
{

}

GameObjectSystem::~GameObjectSystem()
{
}

void GameObjectSystem::Load()
{
  //SpawnGameObject<TileGameObject>()->GetTransform().SetPosition(glm::vec2(1500.0f, 0.0f)); //right
  //SpawnGameObject<TileGameObject>()->GetTransform().SetPosition(glm::vec2(0.0f, 1500.0f)); //up
  //SpawnGameObject<TileGameObject>()->GetTransform().SetPosition(glm::vec2(-1500.0f, 0.0f));  //left
  //SpawnGameObject<PhysicsBodyGameObject>();
  SpawnGameObject<TileGameObject>()->GetTransform().SetPosition(glm::vec2(0.0f, -1500.0f));//down
  SpawnGameObject<DebugGameObject>();
 
  //PhysicsBodyGameObject* objA = SpawnGameObject<PhysicsBodyGameObject>();
  //PhysicsBodyGameObject* objB = SpawnGameObject<PhysicsBodyGameObject>();

  //objA->GetTransform().SetPosition(glm::vec2(-100.0f, 0.0f));
  //objB->GetTransform().SetPosition(glm::vec2(100.0f, 0.0f));

  //objA->GetComponent<RigidBodyComponent>()->GetPhysicsComponent()->SetVelocity(glm::vec2(100.0f, 0.0f)); // left
  //objB->GetComponent<RigidBodyComponent>()->GetPhysicsComponent()->SetVelocity(glm::vec2(-100.0f, 0.0f)); // right

  Engine::Instance()->OnMousePress_.AddFunction(this, &GameObjectSystem::OnMouseClick);
}

void GameObjectSystem::Update(float dt)
{
  auto DestroyGameObjectLambda = [&](std::unique_ptr<IGameObject>& i) { DestroyGameObject(i); };
  std::for_each(gameObjectRegistry_.begin(), gameObjectRegistry_.end(), DestroyGameObjectLambda);

  auto DrawGameObjectLambda = [&](std::unique_ptr<IGameObject>& i) { i->GetDrawList().Broadcast(); };
  std::for_each(gameObjectRegistry_.begin(), gameObjectRegistry_.end(), DrawGameObjectLambda);

  CalculateAndResolveCollisions();

  auto UpdateGameObjectLambda = [&](std::unique_ptr<IGameObject>& i) { i->UpdateGameObject(dt); };
  std::for_each(gameObjectRegistry_.begin(), gameObjectRegistry_.end(), UpdateGameObjectLambda);

  
}

void GameObjectSystem::Unload()
{

}
