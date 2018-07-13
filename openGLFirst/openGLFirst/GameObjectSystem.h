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
 

  virtual void Load() override;
  virtual void Update(float dt) override;
  virtual void Unload() override;

  template<typename GameObject, class... _Types>
  GameObject* SpawnGameObject(_Types&&... _Args)
  {
    GameObject* newGameObject = new GameObject(_Args...);

    AddGameObject(newGameObject);

    return newGameObject;
  }

  void AddGameObject(IGameObject* gameObject);
  void AddCollisionComponent(CollisionComponent* collisionComponent);

  void DestroyGameObject(IGameObject*& gameObjectToDestroy);
  void RemoveCollisonComponent(CollisionComponent* collisionComponent);


  //temp functions
  void CreateObjectRandomly();
private:

  void UpdateCollision();

  GameObjectList gameObjectRegistry_;

  CollisionList activeCollisionGameObjects_;
  CollisionList deactiveCollisionObjects_;
};