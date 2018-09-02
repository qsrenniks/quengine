#include "stdafx.h"
#include "CollisionOccurence.h"
#include "PhysicsComponent.h"
#include "Transform.h"
#include "CollisionComponent.h"
#include "Engine.h"
#include "RigidBodyComponent.h"
#include <iostream>

#include "IGameObject.h"

bool CollisionOccurence::operator==(const CollisionOccurence& otherCollision) const
{
  if (objectA_ == otherCollision.objectA_ && objectB_ == otherCollision.objectB_
      || objectA_ == otherCollision.objectB_ && objectB_ == otherCollision.objectA_ )
  {
    return true;
  }
  else return false;
}

void CollisionOccurence::ResolveVelocities()
{
  PhysicsComponent* physicsA = objectA_->GetPhysicsComponent();
  PhysicsComponent* physicsB = objectB_->GetPhysicsComponent();

  glm::vec2 rv = physicsB->GetVelocity() - physicsA->GetVelocity();
  float contactVel = glm::dot(rv, collisionNormal_);

  if (contactVel > 0)
  {
    return;
  }

  float restitution = std::min(objectA_->bounce_, objectB_->bounce_);
  //impulse scalar
  float j = -(1.0f + restitution) * contactVel;
  j /= physicsA->GetInverseMass() + physicsB->GetInverseMass();

  glm::vec2 impulse = j * collisionNormal_;
  glm::vec2 additiveAVelocity = -physicsA->GetInverseMass() * impulse;
  glm::vec2 additiveBVelocity = physicsB->GetInverseMass() * impulse;

  //glm::vec2 aForce = physicsA->GetMass() * physicsA->GetAcceleration();
  //glm::vec2 bForce = physicsB->GetMass() * physicsB->GetAcceleration();

  ////force in dir of contact normal
  //aForce = -collisionNormal_ * glm::length(aForce);
  //bForce = collisionNormal_ * glm::length(bForce);

  //physicsA->AddForce(aForce);
  //physicsB->AddForce(bForce);

  physicsA->AddVelocity(additiveAVelocity);
  physicsB->AddVelocity(additiveBVelocity);
}

void CollisionOccurence::ResolveInterpenetration()
{
  PhysicsComponent* physicsA = objectA_->GetPhysicsComponent();
  PhysicsComponent* physicsB = objectB_->GetPhysicsComponent();

  Transform& transformA = objectA_->GetParent()->GetTransform();
  Transform& transformB = objectB_->GetParent()->GetTransform();

  const float k_slop = 0.001f; // Penetration allowance
  const float percent = 0.8f; // Penetration percentage to correct
  glm::vec2 correction = (std::max(penetration_ - k_slop, 0.0f) / (physicsA->GetInverseMass() + physicsB->GetInverseMass())) * percent * collisionNormal_;

  transformA.SetPosition(transformA.GetPosition() - physicsA->GetInverseMass() * correction);
  transformB.SetPosition(transformB.GetPosition() + physicsB->GetInverseMass() * correction);

}
