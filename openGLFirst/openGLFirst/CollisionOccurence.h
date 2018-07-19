#pragma once
#include "IComponent.h"
#include <glm/glm.hpp>

class CollisionComponent;
class PhysicsComponent;
class RigidBodyGameObject;
//
// This class is created in the event of a collision in the update loop. 
// if a collision is detected this class is created then pushed onto the gameobjectsystem to later be resolved
//
struct CollisionOccurence
{
public:
  enum class CollisionStatus : int { NOT_COLLIDING, COLLIDING, TOUCHING, INVALID };

  CollisionOccurence(bool isValid = false)
    : collisionStatus_(CollisionStatus::NOT_COLLIDING)
    , mtv_(0.0f)
    //, halfMtv_(0.0f)
    , isValid_(isValid)
  {
  }

  void ConstructNonCollisionOccurence(RigidBodyGameObject* objectA, RigidBodyGameObject* objectB, CollisionStatus collisionStatus);

  //minimal translation vector to properlly resolve a collision
  glm::vec2 mtv_;
  glm::vec2 mtv_AFROMB;
  glm::vec2 mtv_BFROMA;

  //glm::vec2 halfMtv_;
  CollisionStatus collisionStatus_;

  RigidBodyGameObject* objectA_ = nullptr;

  RigidBodyGameObject* objectB_ = nullptr;

  bool IsValid();
  void SetValid(bool validity);

  bool operator==(const CollisionOccurence& otherCollision) const;

  //CollisionOccurence operator-();

  bool isResolved_ = false;

private:

  bool isValid_ = false;
};
