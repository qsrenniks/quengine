#include "stdafx.h"
#include "TileGameObject.h"
#include "CollisionComponent.h"
#include "SpriteComponent.h"

#include "PhysicsComponent.h"
TileGameObject::TileGameObject()
{
  sprite_->SetColor(glm::vec4(0.0f, 0.0f, 1.0f, 1.0f));

  collision_->onEnterOverlap_.AddFunction(this, &TileGameObject::OnOverlapEnter);
  collision_->onExitOverlap_.AddFunction(this, &TileGameObject::OnOverlapExit);

  //physics_->SetRotationalVelocity(45.0f);
  GetTransform().SetScale({ 0.5f, 0.5f });

  //GetPhysicsComponent()->Freeze();
  physics_->SetSimulatePhysics(false);
  GetPhysicsComponent()->SetMass(100000);
  //GetTransform().SetRotation(45.0f);
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
