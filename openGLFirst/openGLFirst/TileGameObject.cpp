#include "stdafx.h"
#include "TileGameObject.h"
#include "CollisionComponent.h"
#include "SpriteComponent.h"

#include "PhysicsComponent.h"
TileGameObject::TileGameObject()
{
  sprite_->SetColor(glm::vec4(0.0f, 0.0f, 1.0f, 1.0f));

  physics_->SetSimulatePhysics(false);
  GetTransform().SetScale({ 10.0f, 10.0f });
  GetPhysicsComponent()->SetMass(0.0f);
}

TileGameObject::~TileGameObject()
{

}

//IGameObject* TileGameObject::Clone()
//{
//  return new TileGameObject();
//}

void TileGameObject::Update(float dt)
{
}

void TileGameObject::OnOverlapEnter(const CollisionOccurence& otherCollider)
{
}

void TileGameObject::OnOverlapExit(const CollisionOccurence& otherCollider)
{
}
