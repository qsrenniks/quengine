#pragma once
#include "IGameplaySystem.h"
#include "IComponent.h"
#include <list>

class IGameObject;
class CollisionComponent;

class GameObjectSystem : public IGameplaySystem
{


public:
  using GameObjectList = std::list<IGameObject*>;
  using CollisionList = std::list<CollisionComponent*>;

  GameObjectSystem() = default;

  virtual ~GameObjectSystem();
  
  virtual void LoadSystem() override;
  virtual void UpdateSystem(float dt) override;
  virtual void UnloadSystem() override;

  void AddGameObject(IGameObject* gameObject);
  void AddCollisionComponent(CollisionComponent* collisionComponent);

  void DestroyGameObject(IGameObject*& gameObjectToDestroy);
  void RemoveCollisonComponent(CollisionComponent* collisionComponent);

private:

  void UpdateCollision();

  GameObjectList gameObjectRegistry_;

  CollisionList collisionGameObjects_;
  
};