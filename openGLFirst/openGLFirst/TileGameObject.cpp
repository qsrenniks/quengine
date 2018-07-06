#include "stdafx.h"
#include "TileGameObject.h"
#include "SpriteComponent.h"
#include "CollisionComponent.h"

TileGameObject::TileGameObject()
{
  AddComponent<SpriteComponent>(sprite_, "vertexShader.vs", "fragmentShader.fs", glm::vec4{ 1.0f, 0.0f, 1.0f, 1.0f }, 0, 1.0f, 1.0f);
  AddComponent<CollisionComponent>(collision_, new SquareCollisionProfile(collision_));
}


TileGameObject::~TileGameObject()
{

}

IGameObject * TileGameObject::Clone()
{
  return new TileGameObject();
}

void TileGameObject::Update(float dt)
{

}
