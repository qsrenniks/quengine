#include "stdafx.h"
#include "PhysicsBodyGameObject.h"
#include "CollisionComponent.h"
#include "PhysicsComponent.h"
#include "SpriteComponent.h"


PhysicsBodyGameObject::PhysicsBodyGameObject()
{
  AddComponent<SpriteComponent>(sprite_, "vertexShader.vs", "fragmentShader.fs", glm::vec4{ 1.0f, 0.0f, 0.0f, 1.0f }, 0, 1.0f, 1.0f);
  AddComponent<PhysicsComponent>(physics_);
  AddComponent<CollisionComponent>(collision_, new SquareCollisionProfile(), new CollisionResponse());

  collision_->onUpdateOverlap_.AddFunction(this, &PhysicsBodyGameObject::OnCollisionUpdate);

  GetTransform().SetScale(glm::vec2(0.1f, 0.1f));
}

PhysicsBodyGameObject::~PhysicsBodyGameObject()
{
}

PhysicsBodyGameObject* PhysicsBodyGameObject::Clone()
{
  return new PhysicsBodyGameObject();
}

void PhysicsBodyGameObject::Update(float dt)
{

}

void PhysicsBodyGameObject::OnCollisionUpdate(CollisionOccurence otherCollider)
{
}
