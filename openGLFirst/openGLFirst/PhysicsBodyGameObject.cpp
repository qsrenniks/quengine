#include "stdafx.h"
#include "PhysicsBodyGameObject.h"
#include "CollisionComponent.h"
#include "PhysicsComponent.h"
#include "SpriteComponent.h"
#include "RigidBodyComponent.h"

PhysicsBodyGameObject::PhysicsBodyGameObject()
{
  sprite_->SetColor(glm::vec4(0.0f, 1.0f, 0.0f, 1.0f));

  AddComponent<RigidBodyComponent>(rigidBody_, 0.0f);

  rigidBody_->GetPhysicsComponent()->AddForceGenerator(new GravityForceGenerator());
  //rigidBody_->GetPhysicsComponent()->SetVelocityDecay(0.90f);

  GetTransform().SetScale(glm::vec2(0.5f, 0.5f));
  //physics_->SetRotationalVelocity(45.0f);

}

PhysicsBodyGameObject::~PhysicsBodyGameObject()
{
}
//
//PhysicsBodyGameObject* PhysicsBodyGameObject::Clone()
//{
//  return new PhysicsBodyGameObject();
//}

void PhysicsBodyGameObject::Update(float dt)
{

}

//void PhysicsBodyGameObject::OnCollisionUpdate(const CollisionOccurence& otherCollider)
//{
//}
