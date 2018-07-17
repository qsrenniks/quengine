#pragma once
#include "IGameplaySystem.h"
#include "IComponent.h"
#include <glm/glm.hpp>
#include <list>

class IGameObject;
class CollisionComponent;

struct CollisionOccurence
{
  enum class CollisionStatus : int { NOT_COLLIDING, COLLIDING, TOUCHING, INVALID };

  CollisionOccurence(bool isValid = false)
    : collisionStatus_(CollisionStatus::NOT_COLLIDING)
    , mtv_(0)
    , isValid_(isValid)
  {
  }

  void ConstructNonCollisionOccurence(CollisionComponent* objectA, CollisionComponent* objectB, CollisionStatus collisionStatus);

  //mtv is always to push b from a 
  glm::vec2 mtv_;
  CollisionStatus collisionStatus_;

  CollisionComponent* objectA_ = nullptr;

  CollisionComponent* objectB_ = nullptr;

  //glm::vec2 objectAsVelocity_ = { 0.0f, 0.0f };
  //float objectAsMass_ = 1;

  //glm::vec2 objectBsVelocity_ = { 0.0f, 0.0f };
  //float objectBsMass_ = 1;


  bool IsValid();
  void SetValid(bool validity);

  bool operator==(CollisionOccurence otherCollision) const;

  CollisionOccurence operator-();

  bool isResolved_ = false;

private:

  bool isValid_ = false;
};

struct CollisionResponse
{
  CollisionResponse() = default;
  ~CollisionResponse() = default;

  virtual void Respond(const CollisionOccurence& occurence);

  void SetCollisionComponent(CollisionComponent* collisionComponent);
  CollisionComponent* GetCollisionComponent() const;
private:

  CollisionComponent * collisionComponent_;

};

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

  void AddCollisionOccurence(CollisionOccurence occurence);
  //void RemoveCollisionOccurence();
  void AddGameObject(IGameObject* gameObject);
  void AddCollisionComponent(CollisionComponent* collisionComponent);

  void DestroyGameObject(IGameObject*& gameObjectToDestroy);
  void RemoveCollisonComponent(CollisionComponent* collisionComponent);

private:

  std::list<CollisionOccurence> collisionOccurences_;

  void CalculateCollisions();
  void ResolveCollisions();
  GameObjectList gameObjectRegistry_;

  CollisionList collisionGameObjects_;
};