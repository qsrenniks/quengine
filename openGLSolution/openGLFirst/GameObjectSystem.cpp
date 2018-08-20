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

#include "NPCollisionProfile.h"
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

void GameObjectSystem::RemoveRigidBodyComponent(RigidBodyComponent* collisionComponent)
{
  rigidBodyComponentRegistry_.remove(collisionComponent);
}

void GameObjectSystem::OnMouseClick(glm::vec2 mousePos)
{
  SpawnGameObject<PhysicsBodyGameObject>()->GetTransform().SetPosition(mousePos);
  //glm::vec2 currentScale = Engine::Instance()->GetViewTransform().GetScale();
  //currentScale.x += 2.0f;
  //currentScale.y += 2.0f;
  //Engine::Instance()->GetViewTransform().SetScale(currentScale);
}

void GameObjectSystem::SaveAllObject()
{
  
}

LevelManager& GameObjectSystem::GetLevelManager()
{
  return levelManager_;
}

void GameObjectSystem::RunCollisionUpdate()
{
  //generates a list of occurences.
  //the occurence is just filled with the objects that might be colliding.
  BroadphaseCollisionDetection();
  //runs through those occurences and resolves them one by one.
  //narrow phase does a deeper check of the objects colliding and then fills the occurences with that information
  //#note this is a very long operation
  NarrowPhaseCollisionDetection();
  //now resolve all collision occurences
  //ResolveAllOccurences();
}

void GameObjectSystem::BroadphaseCollisionDetection()
{
  //generates a list of collision occurences that may or may not be colliding depending on the narrow phase collision detection
  //this performs a simple aabb test.

  for (auto iterStart = rigidBodyComponentRegistry_.begin(); iterStart != rigidBodyComponentRegistry_.end(); iterStart++)
  {
    RigidBodyComponent* objectA = *iterStart;
    for (auto iterInner = iterStart; iterInner != rigidBodyComponentRegistry_.end(); iterInner++)
    {
      RigidBodyComponent* objectB = *iterInner;
      if (objectA == objectB)
      {
        continue;
      }

      //#TODO do broadphase collision check here.
      CollisionStatus status = objectA->GetCollisionComponent()->IsBPCollidingWith(objectB->GetCollisionComponent());

      if (status == CollisionStatus::COLLIDING)
      {
        //std::cout << "Colliding!";

        CollisionOccurence occ;
        occ.objectA_ = objectA;
        occ.objectB_ = objectB;

        //these two objects might be colliding with one another.
        //broadPhaseCollisionPossibilities_.push_back(objectA);
        //broadPhaseCollisionPossibilities_.push_back(objectB);

        collisionOccurences_.push_back(occ);
      }
    } 
  }
}

void GameObjectSystem::NarrowPhaseCollisionDetection()
{
  //iterating throught this multiple times makes sure that they are no longer colliding after the frame.
  //#note this is to reduce the effect of a collision resolution pushing an object back into another object causing another collision
  //#note This could also be improved go going through the list recursively until no collision are registered or at least just the objects are touching. 
  const static int iterations = 8;
  for (int i = 0; i < iterations; i++)
  {
    for (auto& occ : collisionOccurences_)
    {
      occ.objectA_->GetCollisionComponent()->IsNPCollidingWith(occ.objectB_->GetCollisionComponent(), occ);

      occ.objectA_->UpdateCollisionWith(occ.objectB_, occ.collisionStatus_);
      occ.objectB_->UpdateCollisionWith(occ.objectA_, occ.collisionStatus_);
    }
    ResolveAllOccurences();

    //then do another check to make sure they are no longer colliding with anything
    //if they are then redo this.
  }

  //loop through all occurences to make sure no more contacts are occuring.
  //keep going until no more contancts are present.
  collisionOccurences_.clear();
}

void GameObjectSystem::ResolveAllOccurences()
{
  //essentially keep resolving until the objects in all occurences are not penetrating.

  if (collisionOccurences_.empty() == true)
  {
    return;
  }

  for (auto& occ : collisionOccurences_)
  {
    if (occ.collisionStatus_ == CollisionStatus::COLLIDING)
    {
      occ.ResolveVelocities();
      occ.ResolveInterpenetration();
    }
  }

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
  SpawnGameObject<TileGameObject>()->GetTransform().SetPosition(glm::vec2(0.0f, 0.0f));//down
  SpawnGameObject<TileGameObject>()->GetTransform().SetPosition(glm::vec2(1.0f, 0.0f));//down
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
  //auto DestroyGameObjectLambda = [&](std::unique_ptr<IGameObject>& i) { DestroyGameObject(i); };
  //std::for_each(gameObjectRegistry_.begin(), gameObjectRegistry_.end(), DestroyGameObjectLambda);
  auto gameObjectDestructionPredicate = [&](std::unique_ptr<IGameObject>& i) -> bool
  {
    return i->IsMarkedForDestroy();
  };

  gameObjectRegistry_.remove_if(gameObjectDestructionPredicate);

  PhysicsComponent::ForceGeneratorRegistry.ApplyForces();

  auto UpdateGameObjectLambda = [&](std::unique_ptr<IGameObject>& i) { i->UpdateGameObject(dt); };
  std::for_each(gameObjectRegistry_.begin(), gameObjectRegistry_.end(), UpdateGameObjectLambda);

  RunCollisionUpdate();
  
  auto DrawGameObjectLambda = [&](std::unique_ptr<IGameObject>& i) { i->GetDrawList().Broadcast(); };
  std::for_each(gameObjectRegistry_.begin(), gameObjectRegistry_.end(), DrawGameObjectLambda);
}



void GameObjectSystem::Unload()
{

}
