#pragma once
#include "IGameplaySystem.h"
#include "IComponent.h"
#include <list>

class GameObjectSystem : public IGameplaySystem
{


public:
  GameObjectSystem() = default;

  virtual ~GameObjectSystem();
  
  virtual void LoadSystem() override;
  virtual void UpdateSystem(float dt) override;
  virtual void UnloadSystem() override;

  void AddGameObject(class IGameObject *gameObject);
  void AddCollisionComponent(class CollisionComponent *collisionComponent);

  void DestroyGameObject(class IGameObject* gameObject);
  void RemoveCollisonComponent(class CollisionComponent *collisionComponent);

private:

   

  using GameObjectList = std::list<class IGameObject *>;
  GameObjectList gameObjectRegistry_;

  using CollisionList = std::list<class CollisionComponent *>;
  CollisionList collisionGameObjects_;
  
};