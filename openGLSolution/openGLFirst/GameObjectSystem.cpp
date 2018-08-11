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
#include "LoggingSystem.h"

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
  //SpawnGameObject<PhysicsBodyGameObject>()->GetTransform().SetPosition(mousePos);
  glm::vec2 currentScale = Engine::Instance()->GetViewTransform().GetScale();
  currentScale.x += 2.0f;
  currentScale.y += 2.0f;
  Engine::Instance()->GetViewTransform().SetScale(currentScale);
}

void GameObjectSystem::CalculateAndResolveCollisions()
{
  CalculateCollisions();
  //ResolveAllOccurences();
}

void GameObjectSystem::CalculateCollisions()
{
  for (CollisionList::const_iterator itr = rigidBodyComponentRegistry_.cbegin(); itr != rigidBodyComponentRegistry_.cend(); itr++)
  {
    RigidBodyComponent* objectA = *itr;
    for (CollisionList::const_iterator otherItr = itr; otherItr != rigidBodyComponentRegistry_.cend(); otherItr++)
    {
      RigidBodyComponent* objectB = *otherItr;

      if (objectA == objectB)
      {
        continue; 
      }

      //collision check
      CollisionOccurence occ;
      objectA->GetCollisionComponent()->IsCollidingWith(objectB->GetCollisionComponent(), occ);

      //if (occ.collisionStatus_ != CollisionStatus::NOT_COLLIDING)
      //{
      //  //occ.Resolve();
      //  //or add it to the list of resolutions
      //  collisionOccurences_.push_back(occ);
      //  //TODO: fix magic number
      //  occ.ResolveInterpenetration();

      //  //occ.ResolveForces();
      //}
    }
  }
}

void GameObjectSystem::BroadphaseCollisionDetection()
{
  //generates a list of collision occurences that may or may not be colliding depending on the narrow phase collision detection
  //this performs a simple aabb test.
}

void GameObjectSystem::NarrowPhaseCollisionDetection()
{

}

void GameObjectSystem::ResolveAllOccurences()
{
  if (collisionOccurences_.empty() == true)
  {
    return;
  }
  const static int iterations = 10;
  for (int i = 0; i < iterations; i++)
  {
    for (auto& occ : collisionOccurences_)
    {
      occ.ResolveVelocities();
    }
  }

  collisionOccurences_.clear();
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
  //SpawnGameObject<PhysicsBodyGameObject>();
  SpawnGameObject<TileGameObject>()->GetTransform().SetPosition(glm::vec2(0.0f, -0.0f));//down
  SpawnGameObject<DebugGameObject>();
  //SpawnGameObject<TileGameObject>()->GetTransform().SetPosition(glm::vec2(-700.0f, 0.0f));  //left
 
  //PhysicsBodyGameObject* objA = SpawnGameObject<PhysicsBodyGameObject>();
  //PhysicsBodyGameObject* objB = SpawnGameObject<PhysicsBodyGameObject>();
  //PhysicsBodyGameObject* objC = SpawnGameObject<PhysicsBodyGameObject>();
  
  //objA->GetComponent<RigidBodyComponent>()->GetPhysicsComponent()->SetVelocity(glm::vec2(-100.0f, -100.0f));

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

  auto UpdateGameObjectLambda = [&](std::unique_ptr<IGameObject>& i) { i->UpdateGameObject(dt); };
  std::for_each(gameObjectRegistry_.begin(), gameObjectRegistry_.end(), UpdateGameObjectLambda);

  CalculateAndResolveCollisions();
  
  auto DrawGameObjectLambda = [&](std::unique_ptr<IGameObject>& i) { i->GetDrawList().Broadcast(); };
  std::for_each(gameObjectRegistry_.begin(), gameObjectRegistry_.end(), DrawGameObjectLambda);
}

void GameObjectSystem::Unload()
{

}
