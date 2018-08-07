#include "stdafx.h"
#include "PhysicsBodyGameObject.h"
#include "CollisionComponent.h"
#include "PhysicsComponent.h"
#include "SpriteComponent.h"
#include "RigidBodyComponent.h"

PhysicsBodyGameObject::PhysicsBodyGameObject()
{
  sprite_->SetColor(glm::vec4(0.0f, 1.0f, 0.0f, 1.0f));

  AddComponent<RigidBodyComponent>(rigidBody_);

  rigidBody_->GetPhysicsComponent()->AddForceGenerator(new GravityForceGenerator());
  GetTransform().SetScale(glm::vec2(0.5f, 0.5f));

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
