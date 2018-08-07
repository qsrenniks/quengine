#pragma once
#include "IGameplaySystem.h"
#include "CollisionResolution.h"
#include <list>
#include <memory>

class IGameObject;
class CollisionComponent;
class PhysicsComponent;
struct CollisionOccurence;
class RigidBodyComponent;
//
// game object system definition
//
class GameObjectSystem : public IGameplaySystem
{
public:
  static std::string GameObjectSystemLog;

  //ownership of all game objects is to the game object system
  using GameObjectList = std::list<std::unique_ptr<IGameObject>>;

  //this class does not have ownership of the rigidbody components
  //since ownership is not to this class cleanup for this list is not required
  using CollisionList = std::list<RigidBodyComponent*>;

  GameObjectSystem();

  virtual ~GameObjectSystem();
 

  virtual void Load() override;
  virtual void Update(float dt) override;
  virtual void Unload() override;

  template<typename GameObject, class... _Types>
  GameObject* SpawnGameObject(_Types&&... _Args)
  {
    std::unique_ptr<GameObject> newGameObject = std::make_unique<GameObject>(_Args...);
  
    //move invalidates the object so i store the ptr to return later.
    GameObject* newGameObjectPTR = newGameObject.get();

    AddGameObject(std::move(newGameObject));

    return newGameObjectPTR;
  }

  void AddCollisionOccurence(const CollisionOccurence& occurence);
  //void RemoveCollisionOccurence();

  void AddGameObject(std::unique_ptr<IGameObject>&& gameObject);
  void RegisterRigidBodyComponent(RigidBodyComponent* object);

  void DestroyGameObject(std::unique_ptr<IGameObject>& gameObjectToDestroy);
  void RemoveCollisonComponent(RigidBodyComponent* collisionComponent);

  void OnMouseClick(glm::vec2 mousePos);

private:

  void CalculateAndResolveCollisions();

  std::list<CollisionOccurence> collisionOccurences_;

  void CalculateCollisions();
  void ResolveAllOccurences();
  GameObjectList gameObjectRegistry_;

  CollisionList rigidBodyComponentRegistry_;

  //CollisionResolution collisionResolutionSystem_;
  
};