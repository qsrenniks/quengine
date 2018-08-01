#include "stdafx.h"
#include "CollisionOccurence.h"
#include "PhysicsComponent.h"
#include "Transform.h"
#include "CollisionComponent.h"
#include "Engine.h"
#include "RigidBodyComponent.h"

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

  float invMassesSum = objectA_->GetPhysicsComponent()->GetInverseMass() + objectB_->GetPhysicsComponent()->GetInverseMass();
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

  float restitution = std::min(objectA_->bounce_, objectB_->bounce_);

  float impulseScalar = -(1+restitution) * impulseMagnitudeAlongNormal;
  
  float inverseMassSum = physicsA->GetInverseMass() + physicsB->GetInverseMass();
  impulseScalar /= inverseMassSum;

  glm::vec2 impulse = impulseScalar * collisionNormal_;

  float aInvMass = physicsA->GetInverseMass();
  float bInvMass = physicsB->GetInverseMass();

  physicsA->AddVelocity(-(aInvMass * impulse));
  physicsB->AddVelocity(bInvMass* impulse);
}

void CollisionOccurence::ResolveInterpenetration(float dt)
{
  PhysicsComponent* physicsA = objectA_->GetPhysicsComponent();
  PhysicsComponent* physicsB = objectB_->GetPhysicsComponent();

  Transform& transformA = objectA_->GetParent()->GetTransform();
  Transform& transformB = objectB_->GetParent()->GetTransform();


  const static float percentage = 0.2f;
  glm::vec2 correction = penetration_ / (physicsA->GetInverseMass() + physicsB->GetInverseMass()) * percentage * collisionNormal_;

  transformA.SetPosition(transformA.GetPosition() - physicsA->GetInverseMass() * correction);
  transformB.SetPosition(transformB.GetPosition() + physicsB->GetInverseMass() * correction);
}
