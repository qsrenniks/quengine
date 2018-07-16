#include "stdafx.h"
#include "TileGameObject.h"
#include "SpriteComponent.h"
#include "CollisionComponent.h"
#include <iostream>
#include "PhysicsComponent.h"

#include <random>

TileGameObject::TileGameObject()
{
  AddComponent<SpriteComponent>(sprite_, "vertexShader.vs", "fragmentShader.fs", glm::vec4{ 1.0f, 0.0f, 1.0f, 1.0f }, 0, 1.0f, 1.0f);
  AddComponent<CollisionComponent>(collision_, new SquareCollisionProfile(collision_));
  AddComponent<PhysicsComponent>(physics_);

  //physics_->SetAcceleration(PhysicsComponent::Gravity);
  //GetTransform().SetPosition(glm::vec2(0.5f,0.5f));

  //static std::default_random_engine generator;
  //static std::normal_distribution<float> dist(0.0f, 360.0f);

  //GetTransform().SetRotation(dist(generator));
  //physics_->SetRotationalVelocity(45.0f);

  collision_->onEnterOverlap_.AddFunction(this, &TileGameObject::OnOverlapEnter);
  collision_->onExitOverlap_.AddFunction(this, &TileGameObject::OnOverlapExit);

  GetTransform().SetScale({ 0.5f, 0.5f });
}

TileGameObject::~TileGameObject()
{

}

IGameObject* TileGameObject::Clone()
{
  return new TileGameObject();
}

void TileGameObject::Update(float dt)
{
  //physics_->SetAcceleration(glm::vec2(0.0f, -GetTransform().GetPosition().y));

  //if (GetTransform().GetPosition().y <= -0.5f)
  //{
  //  //std::cout << "Something" << std::endl;
  //  physics_->Freeze();
  //}
}

void TileGameObject::OnOverlapEnter(CollisionComponent* otherCollider)
{
  //std::cout << "On overlap Enter! " << std::endl;
  //std::cout << "Intersecting : " << collision_->GetMTV().x << " : " << collision_->GetMTV().y << std::endl;

  //physics_->Freeze();
  //collision_->Disable();
}

void TileGameObject::OnOverlapExit(CollisionComponent* otherCollider)
{
}
