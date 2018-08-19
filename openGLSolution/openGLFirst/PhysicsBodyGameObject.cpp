#include "stdafx.h"
#include "PhysicsBodyGameObject.h"
#include "CollisionComponent.h"
#include "PhysicsComponent.h"
#include "SpriteComponent.h"
#include "RigidBodyComponent.h"
#include "PhysicsForceGenerator.h"

PhysicsBodyGameObject::PhysicsBodyGameObject()
{
  sprite_->SetColor(glm::vec4(0.0f, 1.0f, 0.0f, 1.0f));

  AddComponent<RigidBodyComponent>(rigidBody_);

  PhysicsComponent::ForceGeneratorRegistry.RegisterForceGenerator(rigidBody_->GetPhysicsComponent(), new GravityForceGenerator());

  rigidBody_->GetPhysicsComponent()->SetMass(1.0f);
  GetTransform().SetScale(glm::vec2(0.5f, 0.5f));
  
  //GetTransform().SetRotation(45.0f);
  //rigidBody_->GetPhysicsComponent()->SetRotationalVelocity(45.0f);

}

PhysicsBodyGameObject::~PhysicsBodyGameObject()
{
}

void PhysicsBodyGameObject::Update(float dt)
{
  //rigidBody_->GetPhysicsComponent()->SetVelocity(glm::vec2(-100.0f, 0.0f));
}

//void PhysicsBodyGameObject::OnCollisionUpdate(const CollisionOccurence& otherCollider)
//{
//}
