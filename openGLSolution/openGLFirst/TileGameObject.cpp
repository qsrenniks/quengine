#include "stdafx.h"
#include "TileGameObject.h"
#include "CollisionComponent.h"
#include "SpriteComponent.h"
#include "PhysicsComponent.h"
#include "RigidBodyComponent.h"
#include "BPCollisionProfile.h"

TileGameObject::TileGameObject()
{
  sprite_->SetColor(glm::vec4(0.0f, 0.0f, 1.0f, 1.0f));

  AddComponent<RigidBodyComponent>(rigidBodyComponent_);


  rigidBodyComponent_->GetPhysicsComponent()->SetSimulatePhysics(false);
  //GetTransform().SetScale({ 20.0f, 20.0f });
  rigidBodyComponent_->GetPhysicsComponent()->SetMass(0.0f);

  rigidBodyComponent_->GetCollisionComponent()->GetBPCollisionProfile()->SetAABBExtent(glm::vec2(0.5f, 0.5f));


  rigidBodyComponent_->GetCollisionFilter().SetCollisionType(CT_WorldStatic);
  rigidBodyComponent_->GetCollisionFilter().SetCollisionResponseTo(CT_Player, CollisionResponseType::Blocking);
  rigidBodyComponent_->GetCollisionFilter().SetCollisionResponseTo(CT_WorldStatic, CollisionResponseType::Ignore);

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
