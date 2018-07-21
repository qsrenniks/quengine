#pragma once
#include "IComponent.h"
#include "IGameObject.h"
#include "GameObjectSystem.h"
#include "Delegate.h"
#include "glm/vec2.hpp"
#include <vector>
#include <list>
#include "CollisionOccurence.h"

class CollisionComponent;
//struct CollisionResponse;
class Mesh;

//
// Base class for collision profile. Derive from this to create a new profile with custom collision detection methods
//
class CollisionProfile
{
public:

  CollisionProfile();
  virtual void IsProfileCollidingWith(CollisionProfile* otherProfile, CollisionOccurence& collOcc) const = 0;

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
class PolygonalCollisionProfile : public CollisionProfile
{
public:
  PolygonalCollisionProfile();

  virtual void IsProfileCollidingWith(CollisionProfile* otherProfile, CollisionOccurence& collOcc) const override;

  CollisionOccurence::CollisionStatus PerformAxisProjection(const std::vector<glm::vec2>& axisA, Mesh &meshA, Mesh &meshB, float &overlap, glm::vec2 &smallestAxis) const;

private:

};

//
// This is the definition of the collision component.
//
class CollisionComponent : public IComponent
{
public:
  CollisionComponent(CollisionProfile* collisionProfile /*, CollisionResponse* collisionResponse*/ );
  ~CollisionComponent();
 
  virtual void Update(float dt) override;
  virtual void Draw() override;

  //virtual void Parent(IGameObject* parent) override;

  virtual void Register() override;

  void IsCollidingWith(CollisionComponent* otherCollider, CollisionOccurence& collOcc) const;

private:

  CollisionProfile* collisionProfile_ = nullptr;
};

