#pragma once
#include "IComponent.h"
#include "IGameObject.h"
#include "GameObjectSystem.h"
#include "Delegate.h"
#include "glm/vec2.hpp"
#include <vector>
#include <list>

class CollisionComponent;
struct CollisionResponse;
class Mesh;

//
// Base class for collision profile. Derive from this to create a new profile with custom collision detection methods
//
class CollisionProfile
{
public:

  CollisionProfile();
  virtual void IsProfileCollidingWith(CollisionProfile* otherProfile) const = 0;

  CollisionComponent* GetCollisionComponent();
  void SetCollisionComponent(CollisionComponent* thisCollider);

protected:
  CollisionComponent* collisionComponent_ = nullptr;
};

//
// most rudementary square collision profile that uses the mesh on the sprite component of the object its created with.
// this currenlty should be renamed to polygonal collision profile since it will adapt to the shape of the mesh on the sprite component.
// however it currenlty assumes the mesh is a square and only checks 4 verts. This should later be changed to account for meshes of all verts and shapes.
//
class SquareCollisionProfile : public CollisionProfile
{
public:
  SquareCollisionProfile();

  virtual void IsProfileCollidingWith(CollisionProfile* otherProfile) const override;

  CollisionOccurence::CollisionStatus PerformAxisProjection(std::vector<glm::vec2>& axisA, Mesh &meshA, Mesh &meshB, float &overlap, glm::vec2 &smallestAxis) const;

private:

};

//
// This is the definition of the collision component.
//
class CollisionComponent : public IComponent
{
public: //types
  //using CollidingWithList = std::list<CollisionComponent*>;

public:
  CollisionComponent(CollisionProfile* collisionProfile , CollisionResponse* collisionResponse );
  ~CollisionComponent();
 
  virtual void Update(float dt) override;
  virtual void Draw() override;

  virtual void Parent(IGameObject* parent) override;

  virtual void Register() override;

  void IsCollidingWith(CollisionComponent* otherCollider) const;

  //struct CollisionInformation
  //{
  //  glm::vec2 velocity;
  //  glm::vec2 position;

  //  float rotationalVelocity;

  //  bool isOtherStatic = false;

  //  bool isValid = false;
  //};

  //CollisionInformation RetrieveCollisionInformation(CollisionComponent* collisionComp);

  //informs the collider that it is colliding with another collider
  //void Inform(CollisionComponent* collidingOther);
  //this is called to reset collision information
  //void Reset(CollisionComponent* notCollidingOther);

  delegate<void(CollisionOccurence otherCollider)> onEnterOverlap_;
  delegate<void(CollisionOccurence otherCollider)> onUpdateOverlap_;
  delegate<void(CollisionOccurence otherCollider)> onExitOverlap_;

  //bool GetIsDisabled() const { return isDisabled_; };
  //void Disable() { isDisabled_ = true; };
  //void Enable() { isDisabled_ = false; };

  //void SetMTV(const glm::vec2& mtv);
  //const glm::vec2& GetMTV() const;

  //void IsOverlapping();

  //CollisionComponent* GetOverlappingCollider();

  //void SetCollisionStatus(CollisionStatus collisionStatus);
  //void SetCollisionOccurence(CollisionOccurence newCollisionOccurence);
  //CollisionOccurence& GetCollisionOccurence();
  void InformOfCollision(CollisionOccurence collisionStatus);

  CollisionResponse* GetCollisionResponse();

private:

  CollisionOccurence currentCollisionStatus_;
  //CollisionOccurence collisionOccurence_;

  //bool isDisabled_ = false;

  //bool isOverlappingWithSomething_ = false;

  //glm::vec2 mtv_{0};

  //CollisionComponent* overlappingCollider_ = nullptr;

  CollisionResponse* collisionResponse_ = nullptr;

  CollisionProfile* collisionProfile_ = nullptr;
};

