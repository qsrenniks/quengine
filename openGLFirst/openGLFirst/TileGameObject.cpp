#include "stdafx.h"
#include "TileGameObject.h"
#include "SpriteComponent.h"

TileGameObject::TileGameObject()
{
  AddComponent<SpriteComponent>(sprite_, "vertexShader.vs", "fragmentShader.fs", glm::vec4{ 1.0f, 0.0f, 1.0f, 1.0f }, 0, 0.5f, 0.5f);
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
