#include "stdafx.h"
#include "CollisionComponent.h"
#include "IGameObject.h"
#include "SpriteComponent.h"
#include "CollisionOccurence.h"
#include "RigidBodyComponent.h"

#include "glm/gtc/matrix_transform.hpp"

#include "NPCollisionProfile.h"
#include "BPCollisionProfile.h"
#include "Engine.h"

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
  //GetParent()->GetDrawList().RemoveFunction(this, &CollisionComponent::Draw);
  //GetParent()->GetComponentUpdateList().RemoveFunction(this, &CollisionComponent::Update);

  delete npCollisionProfile_;
  delete bpCollisionProfile_;
}

//#Features_Missing CollisionComponent
// - collision filtering. right now everything collides with everything.
// - no support for overlap colliders.
// - bpCollisionProfile only supports aabb. Line and circle broad phase collision profiles should also be supported at some time.
// - friction has not been implemented.
// - rotation has also been ignored for simplicity.

void CollisionComponent::Update(float dt)
{
  //this is where we update the broadphase collision
  bpCollisionProfile_->UpdateAABB(GetParent()->GetTransform().GetPosition(), GetParent()->GetTransform().GetScale());

  //if (GetParent()->GetTransform().IsDirty() == true)
  //{
    //recalculate normals
    //glm::mat4 rotationalMatrix = glm::rotate(glm::mat4(1.0f), GetParent()->GetTransform().GetRotationD(), glm::vec3(0.0f, 0.0f, 1.0f));
    //npCollisionProfile_->UpdateMesh(rotationalMatrix);
  //}
  //#note this is recalculated every frame. there might be room for optimization when recalculating these values.
  //#note this is also an optimization i could do it in the place where i am actually using the edge normals but then it would happen every iterations. So this needs to be put there
  //and opimized better.
  npCollisionProfile_->npMeshProfile_.RecalculateEdgeNormals(GetParent()->GetTransform().GetRotationR());
}

void CollisionComponent::Draw()
{
  //#TODO this seems like a lot of typing to just get the rendering system
  glm::vec2 bpExtent = bpCollisionProfile_->GetAABBExtent();
  //bpExtent *= 2.0f;
  Engine::Instance()->GetRenderingSystem()->DrawSquare(bpCollisionProfile_->GetAABBLocation(), glm::vec4(1.0f, 1.0f, 1.0f, 1.0f) , bpExtent.x, bpExtent.y, true);

}

void CollisionComponent::Register()
{
  IGameObject* parent = GetParent();

  //i am not registering update function since collision component is updated differently.
  //parent->GetDrawList().AddFunction(this, &CollisionComponent::Draw);
  //parent->GetComponentUpdateList().AddFunction(this, &CollisionComponent::Update);
}

NPCollisionProfile* CollisionComponent::GetNPCollisionProfile() const
{
  return npCollisionProfile_;
}


BPCollisionProfile* CollisionComponent::GetBPCollisionProfile() const
{
  return bpCollisionProfile_;
}

CollisionStatus CollisionComponent::IsNPCollidingWith(CollisionComponent* otherCollider, CollisionOccurence& collOcc)
{
  //#Note here we not only have to determine whether these two objects collided but also how they colliding, meaning
  //more information is needed after the collision has bee calculated. IsProfileCollidingWith is not enough, it must also calculate
  //everything needed for a resolution.

  npCollisionProfile_->SetFillerOccurence(collOcc);

  return npCollisionProfile_->IsProfileCollidingWith(otherCollider->GetNPCollisionProfile());


}

CollisionStatus CollisionComponent::IsBPCollidingWith(CollisionComponent* otherCollider)
{
  //#Note This does an AABB collision check against the other BP collision profile.
  return bpCollisionProfile_->IsProfileCollidingWith(otherCollider->GetBPCollisionProfile());
}
