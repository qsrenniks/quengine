#pragma once
#include "IComponent.h"
#include "IGameObject.h"
#include "GameObjectSystem.h"
#include "Delegate.h"
#include "glm/vec2.hpp"
#include <vector>
#include <list>

class CollisionComponent;
class Mesh;

class CollisionProfile
{
public:

  CollisionProfile(CollisionComponent*& component);
  virtual void IsProfileCollidingWith(CollisionProfile* otherProfile) const = 0;

  CollisionComponent* GetCollisionComponent();

protected:
  CollisionComponent*& collisionComponent_;
};

class SquareCollisionProfile : public CollisionProfile
{
public:
  SquareCollisionProfile(CollisionComponent*&component);

  virtual void IsProfileCollidingWith(CollisionProfile* otherProfile) const override;

  CollisionOccurence::CollisionStatus PerformAxisProjection(std::vector<glm::vec2>& axisA, Mesh &meshA, Mesh &meshB, float &overlap, glm::vec2 &smallestAxis) const;

private:

};

class CollisionComponent : public IComponent
{
public: //types
  //using CollidingWithList = std::list<CollisionComponent*>;

public:
  CollisionComponent(CollisionProfile* collisionProfile);
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

  delegate<void(CollisionComponent* otherCollider)> onEnterOverlap_;
  delegate<void(CollisionComponent* otherCollider)> onUpdateOverlap_;
  delegate<void(CollisionComponent* otherCollider)> onExitOverlap_;

  //bool GetIsDisabled() const { return isDisabled_; };
  //void Disable() { isDisabled_ = true; };
  //void Enable() { isDisabled_ = false; };

  //void SetMTV(const glm::vec2& mtv);
  //const glm::vec2& GetMTV() const;

  //void IsOverlapping();

  CollisionComponent* GetOverlappingCollider();

  //void SetCollisionStatus(CollisionStatus collisionStatus);
  //void SetCollisionOccurence(CollisionOccurence newCollisionOccurence);
  //CollisionOccurence& GetCollisionOccurence();

private:

  //CollisionStatus currentCollisionStatus_;
  //CollisionOccurence collisionOccurence_;

  //bool isDisabled_ = false;

  //bool isOverlappingWithSomething_ = false;

  glm::vec2 mtv_{0};

  CollisionComponent* overlappingCollider_ = nullptr;

  CollisionProfile* collisionProfile_ = nullptr;
};

