#include "stdafx.h"
#include "CollisionComponent.h"
#include "GameObjectSystem.h"
#include "Engine.h"
#include "IGameObject.h"
#include "SpriteComponent.h"
#include <iostream>
#include <algorithm>

CollisionComponent::CollisionComponent(CollisionProfile* profile/*= nullptr*/)
  : collisionProfile_(profile)
{

}

CollisionComponent::~CollisionComponent()
{
  GameObjectSystem* sys = Engine::Instance()->GetGameObjectSystem();
  sys->RemoveCollisonComponent(this);
}

void CollisionComponent::Update(float dt)
{

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
}

bool CollisionComponent::IsCollidingWith(CollisionComponent* otherCollider)
{
  return collisionProfile_->IsProfileCollidingWith(otherCollider->collisionProfile_);
}

void CollisionComponent::Inform(CollisionComponent* collidingOther)
{
  //if you were not previously overlapping with something
  if (isOverlappingWithSomething_ == false && overlappingCollider_ == nullptr)
  {
    //entered overlap
    isOverlappingWithSomething_ = true;
    overlappingCollider_ = collidingOther;
    onEnterOverlap_.Broadcast(collidingOther);
  }
}

void CollisionComponent::Reset(CollisionComponent* notCollidingOther)
{
  //it was previously colliding with something 
  if (isOverlappingWithSomething_ == true && overlappingCollider_ == notCollidingOther)
  {
    isOverlappingWithSomething_ = false;
    onExitOverlap_.Broadcast(overlappingCollider_);
    overlappingCollider_ = nullptr;
  }

  //overlappingCollider_ = nullptr;
}

SquareCollisionProfile::SquareCollisionProfile(CollisionComponent*& component)
  : CollisionProfile(component)
{
  
}

bool SquareCollisionProfile::IsProfileCollidingWith(CollisionProfile* otherProfile)
{
  SpriteComponent* spriteA = component_->GetParent()->GetComponent<SpriteComponent>();
  SpriteComponent* spriteB = otherProfile->GetComponentParent()->GetParent()->GetComponent<SpriteComponent>();

  //get meshes
  Mesh& meshA = spriteA->GetMesh();
  Mesh& meshB = spriteB->GetMesh();

  Transform& transformA = spriteA->GetParent()->GetTransform();
  Transform& transformB = spriteB->GetParent()->GetTransform();

  //get lines
  const glm::vec2& lineUpA = transformA.GetUpVector();
  const glm::vec2& lineRightA = transformA.GetRightVector();
  const glm::vec2& lineUpB = transformB.GetUpVector();
  const glm::vec2& lineRightB = transformB.GetRightVector();

  if (!ProjectMeshesToAxisAndCompare(meshA, lineUpA, meshB)
      || !ProjectMeshesToAxisAndCompare(meshA, lineRightA, meshB)
      || !ProjectMeshesToAxisAndCompare(meshA, lineUpB, meshB)
      || !ProjectMeshesToAxisAndCompare(meshA, lineRightB, meshB))
  {
    return false;
  }
  else
  {
    return true;
  }
}

//returns whether the meshes profiles are overlapping
bool SquareCollisionProfile::ProjectMeshesToAxisAndCompare(Mesh& meshA, const glm::vec2& axisToProjectOn, Mesh& meshB)
{
  bool overlapping = false;

  std::array<float, 4> profileARight = ProjectMeshOntoAxis(meshA, axisToProjectOn);
  std::array<float, 4> profileBRight = ProjectMeshOntoAxis(meshB, axisToProjectOn);
  
  float aMin = *std::min_element(profileARight.begin(), profileARight.end());
  float aMax = *std::max_element(profileARight.begin(), profileARight.end());

  float bMin = *std::min_element(profileBRight.begin(), profileBRight.end());
  float bMax = *std::max_element(profileBRight.begin(), profileBRight.end());

  if ((aMin < bMin && aMax <= bMin) || (aMin >= bMax && aMax > bMax))
  {
    overlapping = false;
  }
  else
  {
    overlapping = true;
  }
  
  return overlapping;
}

std::array<float, 4> SquareCollisionProfile::ProjectMeshOntoAxis(Mesh &meshA, const glm::vec2& axisToProjectOn)
{
  std::array<float, 4> points;

  glm::vec2 meshAVertTopLeft = meshA.GetVertPos(Mesh::TOP_LEFT);
  glm::vec2 meshAVertTopRight = meshA.GetVertPos(Mesh::TOP_RIGHT);
  glm::vec2 meshAVertBottomLeft = meshA.GetVertPos(Mesh::BOTTOM_LEFT);
  glm::vec2 meshAVertBottomRight = meshA.GetVertPos(Mesh::BOTTOM_RIGHT);

  glm::vec2 projectedTopLeft = project(meshAVertTopLeft, axisToProjectOn);
  glm::vec2 projectedTopRight = project(meshAVertTopRight, axisToProjectOn);
  glm::vec2 projectedBottomLeft = project(meshAVertBottomLeft, axisToProjectOn);
  glm::vec2 projectedBottomRight = project(meshAVertBottomRight, axisToProjectOn);

  float dfzTopLeft = glm::dot(axisToProjectOn, projectedTopLeft);
  float dfzTopRight = glm::dot(axisToProjectOn, projectedTopRight);
  float dfzBottomLeft = glm::dot(axisToProjectOn, projectedBottomLeft);
  float dfzBottomRight = glm::dot(axisToProjectOn, projectedBottomRight);

  points[0] = dfzTopLeft;
  points[1] = dfzTopRight;
  points[2] = dfzBottomLeft;
  points[3] = dfzBottomRight;

  return points;
}

glm::vec2 SquareCollisionProfile::project(const glm::vec2& point, const glm::vec2& line)
{
  float numer = glm::dot(point, line);
  float denumer = glm::dot(line, line);

  return (numer / denumer) * line;
}

CollisionProfile::CollisionProfile(CollisionComponent*& component)
  : component_(component)
{
}

CollisionComponent* CollisionProfile::GetComponentParent()
{
  return component_;
}
