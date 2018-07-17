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
  AddComponent<PhysicsComponent>(physics_);
  AddComponent<CollisionComponent>(collision_, new SquareCollisionProfile(), new PhysicalResponse(physics_, true));
  //AddComponent<CollisionComponent>(collision_, new SquareCollisionProfile(), new CollisionResponse());

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
}

void TileGameObject::OnOverlapEnter(CollisionOccurence otherCollider)
{
}

void TileGameObject::OnOverlapExit(CollisionOccurence otherCollider)
{
}
