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
  enum class CollisionStatus : int { NOT_COLLIDING, COLLIDING, INVALID };

  CollisionOccurence()
    : collisionStatus_(CollisionStatus::INVALID)
  {
  }

  void Resolve();

  CollisionStatus collisionStatus_;
  float penetration_;
  float restitution_;
  glm::vec2 collisionNormal_;
  RigidBodyGameObject* objectA_ = nullptr;
  RigidBodyGameObject* objectB_ = nullptr;
  bool operator==(const CollisionOccurence& otherCollision) const;
  bool isResolved_ = false;
private:

  void ResolveVelocities(float dt);
  void ResolveInterpenetration(float dt);
};
