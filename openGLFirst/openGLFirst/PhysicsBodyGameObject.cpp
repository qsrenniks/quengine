#include "stdafx.h"
#include "PhysicsBodyGameObject.h"
#include "CollisionComponent.h"
#include "PhysicsComponent.h"
#include "SpriteComponent.h"
#include "TextLibrary.h"

//std::string PhysicsBodyGameObject::PhysicsBodyGameObjectName = "PhysicsBodyGameObject";

PhysicsBodyGameObject::PhysicsBodyGameObject()
  : IGameObject(TextLibrary::GameObjectNames::PhysicsBodyGameObject)
{
  AddComponent<SpriteComponent>(sprite_, "vertexShader.vs", "fragmentShader.fs", glm::vec4{ 1.0f, 0.0f, 0.0f, 1.0f }, 0, 1.0f, 1.0f);
  AddComponent<PhysicsComponent>(physics_);
  AddComponent<CollisionComponent>(collision_, new SquareCollisionProfile()/*, new PhysicalResponse(physics_, false, 1.0f, 1.0f, 0.1f)*/);

  collision_->onUpdateOverlap_.AddFunction(this, &PhysicsBodyGameObject::OnCollisionUpdate);

  physics_->SetVelocity(glm::vec2(0.1f, -0.1f));
  //physics_->SetAcceleration(PhysicsComponent::Gravity);


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
