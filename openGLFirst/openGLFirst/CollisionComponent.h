#pragma once
#include "IComponent.h"
#include "Delegate.h"
#include "glm/vec2.hpp"
#include <vector>

class CollisionComponent;
class IGameObject;
class Mesh;

class CollisionProfile
{
public:

  CollisionProfile(CollisionComponent*& component);
  virtual bool IsProfileCollidingWith(CollisionProfile* otherProfile) = 0;

  CollisionComponent* GetComponentParent();

protected:
  CollisionComponent*& component_;
};

class SquareCollisionProfile : public CollisionProfile
{
public:
  SquareCollisionProfile(CollisionComponent*&component);

  virtual bool IsProfileCollidingWith(CollisionProfile* otherProfile) override;

  bool ProjectMeshesToAxisAndCompare(Mesh& meshA, const glm::vec2& axisToProjectOn, Mesh& meshB);

  std::array<float, 4> ProjectMeshOntoAxis(Mesh &meshA, const glm::vec2& axisToProjectOn);

private:

  glm::vec2 project(const glm::vec2& point, const glm::vec2& line);
};

class CollisionComponent : public IComponent
{
public:
  CollisionComponent(CollisionProfile* collisionProfile);
  ~CollisionComponent();
 
  virtual void Update(float dt) override;
  virtual void Draw() override;

  virtual void Parent(IGameObject* parent) override;

  virtual void Register() override;

  bool IsCollidingWith(CollisionComponent* otherCollider);

  //informs the collider that it is colliding with another collider
  void Inform(CollisionComponent* collidingOther);
  //this is called to reset collision information
  void Reset(CollisionComponent* notCollidingOther);

  delegate<void(CollisionComponent* otherCollider)> onEnterOverlap_;
  delegate<void(CollisionComponent* otherCollider)> onExitOverlap_;

  bool GetIsDisabled() const { return isDisabled_; };
  void Disable() { isDisabled_ = true; };
  void Enable() { isDisabled_ = false; };

private:

  bool isDisabled_ = false;

  bool isOverlappingWithSomething_ = false;

  CollisionComponent* overlappingCollider_ = nullptr;

  CollisionProfile* collisionProfile_;
};

