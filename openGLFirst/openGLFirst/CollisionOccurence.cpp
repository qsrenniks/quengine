#include "stdafx.h"
#include "CollisionOccurence.h"
#include "PhysicsComponent.h"
#include "RigidBodyGameObject.h"
#include "Transform.h"
#include "CollisionComponent.h"
#include "Engine.h"

bool CollisionOccurence::operator==(const CollisionOccurence& otherCollision) const
{
  if (objectA_ == otherCollision.objectA_ && objectB_ == otherCollision.objectB_
      || objectA_ == otherCollision.objectB_ && objectB_ == otherCollision.objectA_ )
  {
    return true;
  }
  else return false;
}

void CollisionOccurence::Resolve()
{
  float dt = Engine::Instance()->GetDeltaTime();

  float invMassesSum = objectA_->GetPhysicsComponent()->GetPhysicsProperties().GetInverseMass() + objectB_->GetPhysicsComponent()->GetPhysicsProperties().GetInverseMass();
  if (invMassesSum == 0.0f)
  {
    return;
  }

  ResolveVelocities(dt);
  ResolveInterpenetration(dt);
}

void CollisionOccurence::ResolveVelocities(float dt)
{
  PhysicsComponent* physicsA = objectA_->GetPhysicsComponent();
  PhysicsComponent* physicsB = objectB_->GetPhysicsComponent();

  glm::vec2 relativeVelocity = physicsB->GetVelocity() - physicsA->GetVelocity();

  float impulseMagnitudeAlongNormal = glm::dot(relativeVelocity, collisionNormal_);

  if (impulseMagnitudeAlongNormal > 0)
  {
    return;
  }

  float restitution = std::min(physicsA->GetPhysicsProperties().bounce_, physicsB->GetPhysicsProperties().bounce_);

  float impulseScalar = -(1+restitution) * impulseMagnitudeAlongNormal;
  
  float inverseMassSum = physicsA->GetPhysicsProperties().GetInverseMass() + physicsB->GetPhysicsProperties().GetInverseMass();
  impulseScalar /= inverseMassSum;

  glm::vec2 impulse = impulseScalar * collisionNormal_;

  float aInvMass = physicsA->GetPhysicsProperties().GetInverseMass();
  float bInvMass = physicsB->GetPhysicsProperties().GetInverseMass();

  physicsA->AddVelocity(-(aInvMass * impulse));
  physicsB->AddVelocity(bInvMass* impulse);
}

void CollisionOccurence::ResolveInterpenetration(float dt)
{
  PhysicsComponent* physicsA = objectA_->GetPhysicsComponent();
  PhysicsComponent* physicsB = objectB_->GetPhysicsComponent();

  const static float percentage = 0.2f;
  glm::vec2 correction = penetration_ / (physicsA->GetPhysicsProperties().GetInverseMass() + physicsB->GetPhysicsProperties().GetInverseMass()) * percentage * collisionNormal_;

  objectA_->GetTransform().SetPosition(objectA_->GetTransform().GetPosition() - physicsA->GetPhysicsProperties().GetInverseMass() * correction);
  objectB_->GetTransform().SetPosition(objectB_->GetTransform().GetPosition() + physicsB->GetPhysicsProperties().GetInverseMass() * correction);
}
