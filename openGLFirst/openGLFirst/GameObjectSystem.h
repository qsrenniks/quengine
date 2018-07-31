#pragma once
#include "IGameplaySystem.h"
#include "CollisionResolution.h"
#include <list>

class IGameObject;
class CollisionComponent;
class PhysicsComponent;
struct CollisionOccurence;
class RigidBodyGameObject;

//
// game object system definition
//
class GameObjectSystem : public IGameplaySystem
{
public:
  static std::string GameObjectSystemLog;

  using GameObjectList = std::list<IGameObject*>;
  using CollisionList = std::list<RigidBodyGameObject*>;

  GameObjectSystem();

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

  template<typename Component, class... _Types>
  Component* SpawnComponent(_Types&&... _Args)
  {
    Component* newComponent = new Component(_Args...);

    //do something here to register it with the system.

    return newComponent;
  }

  void AddCollisionOccurence(const CollisionOccurence& occurence);
  //void RemoveCollisionOccurence();
  void AddGameObject(IGameObject* gameObject);
  void AddRigidBodyGameObject(RigidBodyGameObject* object);

  void DestroyGameObject(IGameObject*& gameObjectToDestroy);
  void RemoveCollisonComponent(RigidBodyGameObject* collisionComponent);

  void OnMouseClick(glm::vec2 mousePos);

private:

  void CalculateAndResolveCollisions();

  std::list<CollisionOccurence> collisionOccurences_;

  void CalculateCollisions();
  void ResetBodies();
  GameObjectList gameObjectRegistry_;

  CollisionList collisionGameObjects_;

  //CollisionResolution collisionResolutionSystem_;
  
};