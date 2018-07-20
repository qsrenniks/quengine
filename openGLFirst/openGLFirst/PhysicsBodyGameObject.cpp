#include "stdafx.h"
#include "PhysicsBodyGameObject.h"
#include "CollisionComponent.h"
#include "PhysicsComponent.h"
#include "SpriteComponent.h"

PhysicsBodyGameObject::PhysicsBodyGameObject()
{
  //collision_->onUpdateOverlap_.AddFunction(this, &PhysicsBodyGameObject::OnCollisionUpdate);

  sprite_->SetColor(glm::vec4(0.0f, 1.0f, 0.0f, 1.0f));

  physics_->SetAcceleration(PhysicsComponent::Gravity);

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
