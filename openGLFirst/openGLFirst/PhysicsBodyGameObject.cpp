#include "stdafx.h"
#include "PhysicsBodyGameObject.h"
#include "CollisionComponent.h"
#include "PhysicsComponent.h"
#include "SpriteComponent.h"

PhysicsBodyGameObject::PhysicsBodyGameObject()
{
  //collision_->onUpdateOverlap_.AddFunction(this, &PhysicsBodyGameObject::OnCollisionUpdate);

  sprite_->SetColor(glm::vec4(0.0f, 1.0f, 0.0f, 1.0f));

  physics_->AddForceGenerator(new GravityForceGenerator());
  physics_->SetBounce(0.0f);
  physics_->SetVelocityDecay(0.90f);

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
