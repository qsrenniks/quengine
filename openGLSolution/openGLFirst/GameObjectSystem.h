#pragma once
#include "IGameplaySystem.h"
#include <list>
#include <memory>
#include "CollisionOccurence.h"
#include "LevelManager.h"

class IGameObject;
class CollisionComponent;
class PhysicsComponent;
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
  
    //move invalidates the object so i store the ptr to areturn later.
    GameObject* newGameObjectPTR = newGameObject.get();

    AddGameObject(std::move(newGameObject));

    return newGameObjectPTR;
  }

  template<typename GameObject, class... _Types>
  GameObject* SpawnGameObjectAtLocation(const glm::vec2& location, _Types&&... _Args)
  {
    std::unique_ptr<GameObject> newGameObject = std::make_unique<GameObject>(_Args...);
  
    GameObject* newGameObjectPtr = newGameObject.get();

    newGameObjectPtr->SetLocation(location);

    AddGameObject(std::move(newGameObject));

    return newGameObjectPtr;
  }
  
  void SaveGame();
  void LoadGame();

  void AddCollisionOccurence(const CollisionOccurence& occurence);
  //void RemoveCollisionOccurence();

  void AddGameObject(std::unique_ptr<IGameObject>&& gameObject);
  void RegisterRigidBodyComponent(RigidBodyComponent* object);

  void RemoveRigidBodyComponent(RigidBodyComponent* collisionComponent);

  void OnMouseClick(glm::vec2 mousePos);

  void SaveAllObject();

  LevelManager& GetLevelManager();

private:

  void RunCollisionUpdate();

  void BroadphaseCollisionDetection();
  void NarrowPhaseCollisionDetection();
  void ResolveAllOccurences();

  std::list<CollisionOccurence> collisionOccurences_;

  CollisionList rigidBodyComponentRegistry_;

  //#note this has to be last in the list of game object registries, since it must be destroyed 
  //last in order to maintain the other lists for object clean up during gameplay.
  GameObjectList gameObjectRegistry_;

  LevelManager levelManager_;
};