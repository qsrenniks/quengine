#include "stdafx.h"
#include "CollisionComponent.h"
#include "GameObjectSystem.h"
#include "Engine.h"
#include "IGameObject.h"
#include "SpriteComponent.h"
#include <iostream>
#include <algorithm>
#include "PhysicsComponent.h"

CollisionComponent::CollisionComponent(CollisionProfile* profile/*= nullptr*/)
  : collisionProfile_(profile)
{

}

CollisionComponent::~CollisionComponent()
{
  GameObjectSystem* sys = Engine::Instance()->GetGameObjectSystem();
  sys->RemoveCollisonComponent(this);

  delete collisionProfile_;
}

void CollisionComponent::Update(float dt)
{
  if (isOverlappingWithSomething_)
  {
    onUpdateOverlap_.Broadcast(overlappingColliders_);
  }
}

void CollisionComponent::Draw()
{

}

void CollisionComponent::Parent(IGameObject* parent)
{
  IComponent::Parent(parent);

  GameObjectSystem* sys = Engine::Instance()->GetGameObjectSystem();
  sys->AddCollisionComponent(this);
}

void CollisionComponent::Register()
{
  IGameObject* parent = GetParent();

  //i am not registering update function since collision component is updated differently.
  parent->GetDrawList().AddFunction(this, &CollisionComponent::Draw);
  parent->GetComponentUpdateList().AddFunction(this, &CollisionComponent::Update);
}

bool CollisionComponent::IsCollidingWith(CollisionComponent* otherCollider) const
{
  return collisionProfile_->IsProfileCollidingWith(otherCollider->collisionProfile_);
}

CollisionComponent::CollisionInformation CollisionComponent::RetrieveCollisionInformation(CollisionComponent* collComp)
{
  if (!isOverlappingWithSomething_)
  {
    return CollisionInformation();
  }
  
  if (std::find(overlappingColliders_.cbegin(), overlappingColliders_.cend(), collComp) == overlappingColliders_.cend())
  {
    //something weird has happened
    assert(false);
  }

  CollisionInformation collInfo;

  PhysicsComponent* otherPhys = collComp->GetParent()->GetComponent<PhysicsComponent>();

  if (otherPhys != nullptr)
  {
    collInfo.rotationalVelocity = otherPhys->GetRotationalVelocity();
    collInfo.velocity = otherPhys->GetVelocity();
    collInfo.isOtherStatic = otherPhys->GetIsStatic();
  }
  else
  {
    collInfo.isOtherStatic = true;
  }
  
  collInfo.isValid = true;
  return collInfo;
}

//only called when a collision has occurred
void CollisionComponent::Inform(CollisionComponent* collidingOther)
{
  //if it does not find this collider already in the lsit then add it 
  if (std::find(overlappingColliders_.cbegin(), overlappingColliders_.cend(), collidingOther) == overlappingColliders_.cend())
  {
    isOverlappingWithSomething_ = true;
    overlappingColliders_.push_back(collidingOther);
    onEnterOverlap_.Broadcast(collidingOther);
  }
}

void CollisionComponent::Reset(CollisionComponent* notCollidingOther)
{
  //it was previously colliding with something 
  if (isOverlappingWithSomething_ == true && std::find(overlappingColliders_.cbegin(), overlappingColliders_.cend(), notCollidingOther) != overlappingColliders_.cend())
  {
    onExitOverlap_.Broadcast(notCollidingOther);
    overlappingColliders_.remove(notCollidingOther);
  }

  if (overlappingColliders_.size() == 0)
  {
    isOverlappingWithSomething_ = false;
  }
}

void CollisionComponent::SetMTV(const glm::vec2& mtv)
{
  mtv_ = mtv;
}

const glm::vec2& CollisionComponent::GetMTV() const
{
  return mtv_;
}

SquareCollisionProfile::SquareCollisionProfile(CollisionComponent*& component)
  : CollisionProfile(component)
{
  
}

bool SquareCollisionProfile::IsProfileCollidingWith(CollisionProfile* otherProfile) const
{
  SpriteComponent* spriteA = collisionComponent_->GetParent()->GetComponent<SpriteComponent>();
  SpriteComponent* spriteB = otherProfile->GetCollisionComponent()->GetParent()->GetComponent<SpriteComponent>();

  //get meshes
  Mesh& meshA = spriteA->GetMesh();
  Mesh& meshB = spriteB->GetMesh();

  Transform& transformA = spriteA->GetParent()->GetTransform();
  Transform& transformB = spriteB->GetParent()->GetTransform();

  std::vector<glm::vec2> axisA;
  std::vector<glm::vec2> axisB;

  meshA.GetAxis(axisA, transformA.BuildTransform());
  meshB.GetAxis(axisB, transformB.BuildTransform());

  float overlap = std::numeric_limits<float>::max();
  glm::vec2 smallestAxis;

  for (glm::vec2& line : axisA)
  {
    line = glm::normalize(line);

    Mesh::Projection meshAProjected = meshA.project(line);
    Mesh::Projection meshBProjected = meshB.project(line);
      
    //returns true if overlapping and false if not
    if (!meshAProjected.IsOverlapping(meshBProjected))
    {
      return false;
    }
    else
    {
      float o = meshAProjected.GetOverlap(meshBProjected);

      if (o < overlap)
      {
        overlap = o;
        smallestAxis = line;
      }
    }
  }

  for (glm::vec2& line : axisB)
  {
    line = glm::normalize(line);

    Mesh::Projection meshAProjected = meshA.project(line);
    Mesh::Projection meshBProjected = meshB.project(line);

    //returns true if overlapping and false if not
    if (!meshAProjected.IsOverlapping(meshBProjected))
    {
      return false;
    }
    else
    {
      float o = meshAProjected.GetOverlap(meshBProjected);

      if (o < overlap)
      {
        overlap = o;
        smallestAxis = line;
      }
    }
  }


  glm::vec2 mtv = smallestAxis * overlap;
  collisionComponent_->SetMTV(mtv);
  otherProfile->GetCollisionComponent()->SetMTV(mtv);
  return true;
}

//returns whether the meshes profiles are overlapping
//bool SquareCollisionProfile::ProjectMeshesToAxisAndCompare(Mesh& meshA, const glm::vec2& axisToProjectOn, Mesh& meshB, glm::vec2& mtv) const
//{
//  float aMin;
//  float aMax;
//  float bMin;
//  float bMax;
//
//  ProjectMeshOntoAxis(meshA, axisToProjectOn, aMin, aMax);
//  ProjectMeshOntoAxis(meshB, axisToProjectOn, bMin, bMax);
//
//  if ((aMax <= bMin) || (aMin >= bMax))
//  {
//    return false;
//  }
//  //there are overlapping, so by how much?
//  //else
//  //{
//  //  glm::vec2 overlap;
//  //  if (aMax > bMin)
//  //  {
//  //    overlap = bMin - aMax
//  //  }
//  //  else if (aMin < bMax)
//  //  {
//  //    overlap = bMax - aMin;
//  //  }
//
//  //  if (overlap.operator<(mtv))
//  //  {
//  //    mtv = overlap
//  //  }
//
//  //}
//  
//  return true;
//}

//void SquareCollisionProfile::ProjectMeshOntoAxis(Mesh &meshA, const glm::vec2& axisToProjectOn, float& min, float &max) const
//{
//  std::array<float, 4> points;
//
//  glm::vec2 meshAVertTopLeft = meshA.GetVertPos(Mesh::TOP_LEFT);
//  glm::vec2 meshAVertTopRight = meshA.GetVertPos(Mesh::TOP_RIGHT);
//  glm::vec2 meshAVertBottomLeft = meshA.GetVertPos(Mesh::BOTTOM_LEFT);
//  glm::vec2 meshAVertBottomRight = meshA.GetVertPos(Mesh::BOTTOM_RIGHT);
//
//  glm::vec2 projectedTopLeft = project(meshAVertTopLeft, axisToProjectOn);
//  glm::vec2 projectedTopRight = project(meshAVertTopRight, axisToProjectOn);
//  glm::vec2 projectedBottomLeft = project(meshAVertBottomLeft, axisToProjectOn);
//  glm::vec2 projectedBottomRight = project(meshAVertBottomRight, axisToProjectOn);
//
//  float dfzTopLeft = glm::dot(axisToProjectOn, projectedTopLeft);
//  float dfzTopRight = glm::dot(axisToProjectOn, projectedTopRight);
//  float dfzBottomLeft = glm::dot(axisToProjectOn, projectedBottomLeft);
//  float dfzBottomRight = glm::dot(axisToProjectOn, projectedBottomRight);
//
//  points[0] = dfzTopLeft;
//  points[1] = dfzTopRight;
//  points[2] = dfzBottomLeft;
//  points[3] = dfzBottomRight;
//
//  min = *std::min_element(points.begin(), points.end());
//  max = *std::max_element(points.begin(), points.end());
//}

//glm::vec2 SquareCollisionProfile::project(const glm::vec2& point, const glm::vec2& line) const
//{
//  return (glm::dot(point, line) / glm::dot(line, line)) * line;
//}

CollisionProfile::CollisionProfile(CollisionComponent*& component)
  : collisionComponent_(component)
{
}

CollisionComponent* CollisionProfile::GetCollisionComponent()
{
  return collisionComponent_;
}
