#include "stdafx.h"
#include "TileGameObject.h"
#include "SpriteComponent.h"
#include "CollisionComponent.h"
#include <iostream>
#include "PhysicsComponent.h"

#include <random>

std::string TileGameObject::TileGameObjectName = "TileGameObject";

TileGameObject::TileGameObject()
  : IGameObject(TileGameObjectName)
{
  AddComponent<SpriteComponent>(sprite_, "vertexShader.vs", "fragmentShader.fs", glm::vec4{ 1.0f, 0.0f, 1.0f, 1.0f }, 0, 1.0f, 1.0f);
  AddComponent<PhysicsComponent>(physics_);
  AddComponent<CollisionComponent>(collision_, new SquareCollisionProfile(), new PhysicalResponse(physics_, true));
  //AddComponent<CollisionComponent>(collision_, new SquareCollisionProfile(), new DebugResponse());

  collision_->onEnterOverlap_.AddFunction(this, &TileGameObject::OnOverlapEnter);
  collision_->onExitOverlap_.AddFunction(this, &TileGameObject::OnOverlapExit);

  //physics_->SetRotationalVelocity(45.0f);
  GetTransform().SetScale({ 0.5f, 0.5f });
  //GetTransform().SetRotation(45.0f);
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
}

void TileGameObject::OnOverlapEnter(CollisionOccurence otherCollider)
{
}

void TileGameObject::OnOverlapExit(CollisionOccurence otherCollider)
{
}
