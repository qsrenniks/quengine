#pragma once
#include "IComponent.h"
#include "glm/vec2.hpp"
#include <vector>

class CollisionComponent;
class IGameObject;
class Mesh;

class CollisionProfile
{
public:

  CollisionProfile(CollisionComponent *&component);
  virtual bool IsProfileCollidingWith(CollisionProfile *otherProfile) = 0;

  CollisionComponent *GetComponentParent();

protected:
  CollisionComponent *&component_;
};

class SquareCollisionProfile : public CollisionProfile
{
public:
  SquareCollisionProfile(CollisionComponent *&component);

  virtual bool IsProfileCollidingWith(CollisionProfile *otherProfile) override;

  bool ProjectMeshesToAxisAndCompare(Mesh& meshA, glm::vec2 lineRightA, Mesh& meshB);

  std::array<float, 4> ProjectMeshOntoAxis(Mesh &meshA, glm::vec2 lineUpA);

private:

  glm::vec2 project(const glm::vec2& point, const glm::vec2& line);
};

class CollisionComponent : public IComponent
{
public:
  CollisionComponent(CollisionProfile * = nullptr);
  ~CollisionComponent();

  virtual void Update(float dt) override;
  virtual void Draw() override;

  virtual void Parent(IGameObject *parent) override;

  virtual void Register() override;

  bool IsCollidingWith(CollisionComponent * otherCollider);

private:

  CollisionProfile * collisionProfile_;
};

