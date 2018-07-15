#pragma once
#include "IComponent.h"
#include "Delegate.h"
#include "glm/vec2.hpp"
#include <vector>
#include <list>

class CollisionComponent;
class IGameObject;
class Mesh;

class CollisionProfile
{
public:

  CollisionProfile(CollisionComponent*& component);
  virtual bool IsProfileCollidingWith(CollisionProfile* otherProfile) const = 0;

  CollisionComponent* GetCollisionComponent();

protected:
  CollisionComponent*& collisionComponent_;
};

class SquareCollisionProfile : public CollisionProfile
{
public:
  SquareCollisionProfile(CollisionComponent*&component);

  virtual bool IsProfileCollidingWith(CollisionProfile* otherProfile) const override;

  //bool ProjectMeshesToAxisAndCompare(Mesh& meshA, const glm::vec2& axisToProjectOn, Mesh& meshB, glm::vec2& mtv) const;

  //void ProjectMeshOntoAxis(Mesh &meshA, const glm::vec2& axisToProjectOn, float& min, float& max) const;

private:

  //glm::vec2 project(const glm::vec2& point, const glm::vec2& line) const;
};

class CollisionComponent : public IComponent
{
public: //types
  using CollidingWithList = std::list<CollisionComponent*>;

public:
  CollisionComponent(CollisionProfile* collisionProfile);
  ~CollisionComponent();
 
  virtual void Update(float dt) override;
  virtual void Draw() override;

  virtual void Parent(IGameObject* parent) override;

  virtual void Register() override;

  bool IsCollidingWith(CollisionComponent* otherCollider) const;

  struct CollisionInformation
  {
    glm::vec2 velocity;
    glm::vec2 position;

    float rotationalVelocity;

    bool isOtherStatic = false;

    bool isValid = false;
  };

  CollisionInformation RetrieveCollisionInformation(CollisionComponent* collisionComp);

  //informs the collider that it is colliding with another collider
  void Inform(CollisionComponent* collidingOther);
  //this is called to reset collision information
  void Reset(CollisionComponent* notCollidingOther);

  delegate<void(CollisionComponent* otherCollider)> onEnterOverlap_;
  delegate<void(CollidingWithList&)> onUpdateOverlap_;
  delegate<void(CollisionComponent* otherCollider)> onExitOverlap_;

  bool GetIsDisabled() const { return isDisabled_; };
  void Disable() { isDisabled_ = true; };
  void Enable() { isDisabled_ = false; };

  void SetMTV(const glm::vec2& mtv);
  const glm::vec2& GetMTV() const;

  bool IsOverlapping();

  CollidingWithList& GetOverlappingColliders();

private:

  bool isDisabled_ = false;

  bool isOverlappingWithSomething_ = false;

  glm::vec2 mtv_{0};

  CollidingWithList overlappingColliders_;

  CollisionProfile* collisionProfile_;
};

