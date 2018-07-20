#include "stdafx.h"
#include "PhysicsBodyGameObject.h"
#include "CollisionComponent.h"
#include "PhysicsComponent.h"
#include "SpriteComponent.h"

PhysicsBodyGameObject::PhysicsBodyGameObject()
{
  //collision_->onUpdateOverlap_.AddFunction(this, &PhysicsBodyGameObject::OnCollisionUpdate);

  sprite_->SetColor(glm::vec4(0.0f, 1.0f, 0.0f, 1.0f));
  physics_->SetBounce(0.0f);
  //physics_->SetFriction(0.0f);
  physics_->SetVelocityDecay(1.0f);
  //physics_->SetAcceleration(PhysicsComponent::Gravity);
  //physics_->SetSimulatePhysics(false);
  physics_->SetMass(1.0f);
  //physics_->SetRotationalVelocity(15.0f);

  //physics_->SetVelocity(glm::vec2(0.5f, -0.5f)); 

  GetTransform().SetScale(glm::vec2(0.1f, 0.1f));
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
