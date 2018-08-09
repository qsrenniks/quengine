#include "stdafx.h"
#include "CollisionComponent.h"
#include "IGameObject.h"
#include "SpriteComponent.h"
#include "CollisionOccurence.h"
#include "RigidBodyComponent.h"

#include "NPCollisionProfile.h"
#include "BPCollisionProfile.h"

CollisionComponent::CollisionComponent(NPCollisionProfile* npCollisionProfile, BPCollisionProfile* bpCollisionProfile)
  : npCollisionProfile_(npCollisionProfile)
  , bpCollisionProfile_(bpCollisionProfile)
  //, collisionResponse_(collisionResponse)
{
  npCollisionProfile_->SetCollisionComponent(this);
  //collisionResponse_->SetCollisionComponent(this);
}

CollisionComponent::~CollisionComponent()
{
  delete npCollisionProfile_;
}

void CollisionComponent::Update(float dt)
{
  //this is where we update the broadphase collision
}

void CollisionComponent::Draw()
{
  //this might draw the aabb box for the broadphase collision detection system.
}

void CollisionComponent::Register()
{
  IGameObject* parent = GetParent();

  //i am not registering update function since collision component is updated differently.
  parent->GetDrawList().AddFunction(this, &CollisionComponent::Draw);
  parent->GetComponentUpdateList().AddFunction(this, &CollisionComponent::Update);
}

void CollisionComponent::IsCollidingWith(CollisionComponent* otherCollider, CollisionOccurence& collOcc) const
{
  npCollisionProfile_->IsProfileCollidingWith(otherCollider->npCollisionProfile_, collOcc);
}

