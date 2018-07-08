#include "stdafx.h"
#include "CollisionComponent.h"
#include "GameObjectSystem.h"
#include "Engine.h"
#include "IGameObject.h"
#include "SpriteComponent.h"
#include <iostream>
#include <algorithm>

CollisionComponent::CollisionComponent(CollisionProfile *profile/*= nullptr*/)
  : collisionProfile_(profile)
{

}

CollisionComponent::~CollisionComponent()
{
  GameObjectSystem* sys = Engine::Instance()->GetSystem<GameObjectSystem>();
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

  GameObjectSystem* sys = Engine::Instance()->GetSystem<GameObjectSystem>();
  sys->AddCollisionComponent(this);
}

void CollisionComponent::Register()
{
  IGameObject *parent = GetParent();

  //i am not registering update function since collision component is updated differently.
  parent->GetDrawList().AddFunction(this, &CollisionComponent::Draw);
}

bool CollisionComponent::IsCollidingWith(CollisionComponent *otherCollider)
{
  return collisionProfile_->IsProfileCollidingWith(otherCollider->collisionProfile_);
}

SquareCollisionProfile::SquareCollisionProfile(CollisionComponent*& component)
  : CollisionProfile(component)
{
  
}

bool SquareCollisionProfile::IsProfileCollidingWith(CollisionProfile* otherProfile)
{
  bool intersecting = false;

  SpriteComponent* spriteA = component_->GetParent()->GetComponent<SpriteComponent>();
  SpriteComponent* spriteB = otherProfile->GetComponentParent()->GetParent()->GetComponent<SpriteComponent>();

  //get meshes
  Mesh& meshA = spriteA->GetMesh();
  Mesh& meshB = spriteB->GetMesh();

  //get lines
  glm::vec2 lineUpA = spriteA->GetParent()->GetTransform().GetUpVector();
  glm::vec2 lineRightA = spriteA->GetParent()->GetTransform().GetRightVector();
  glm::vec2 lineUpB = spriteB->GetParent()->GetTransform().GetUpVector();
  glm::vec2 lineRightB = spriteB->GetParent()->GetTransform().GetRightVector();

  //im not rotating the fucking mesh in real time. just in rendering time wtf.
  bool a = ProjectMeshesToAxisAndCompare(meshA, lineUpA, meshB);

  bool b = ProjectMeshesToAxisAndCompare(meshA, lineRightA, meshB);

  bool c = ProjectMeshesToAxisAndCompare(meshA, lineUpB, meshB);

  bool d = ProjectMeshesToAxisAndCompare(meshA, lineRightB, meshB);
  
  if (!a || !b || !c || !d)
  {
    intersecting = false;
  }
  else
  {
    intersecting = true;
  }

  return intersecting;
}

//returns whether the meshes profiles are overlapping
bool SquareCollisionProfile::ProjectMeshesToAxisAndCompare(Mesh& meshA, glm::vec2 lineRightA, Mesh& meshB)
{
  bool overlapping = false;
  //TODO: im only doing 2 checks here
  //grep profiles
  std::array<float, 4> profileARight = ProjectMeshOntoAxis(meshA, lineRightA);
  std::array<float, 4> profileBRight = ProjectMeshOntoAxis(meshB, lineRightA);
  
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

std::array<float, 4> SquareCollisionProfile::ProjectMeshOntoAxis(Mesh &meshA, glm::vec2 lineUpA)
{
  std::array<float, 4> points;

  glm::vec2 meshAVertTopLeft = meshA.GetVertPos(Mesh::TOP_LEFT);
  glm::vec2 meshAVertTopRight = meshA.GetVertPos(Mesh::TOP_RIGHT);
  glm::vec2 meshAVertBottomLeft = meshA.GetVertPos(Mesh::BOTTOM_LEFT);
  glm::vec2 meshAVertBottomRight = meshA.GetVertPos(Mesh::BOTTOM_RIGHT);

  glm::vec2 projectedTopLeft = project(meshAVertTopLeft, lineUpA);
  glm::vec2 projectedTopRight = project(meshAVertTopRight, lineUpA);
  glm::vec2 projectedBottomLeft = project(meshAVertBottomLeft, lineUpA);
  glm::vec2 projectedBottomRight = project(meshAVertBottomRight, lineUpA);

  //float dfzTopLeft = glm::distance(glm::vec2(0.0f, 0.0f), projectedTopLeft);
  //float dfzTopRight = glm::distance(glm::vec2(0.0f, 0.0f), projectedTopRight);
  //float dfzBottomLeft = glm::distance(glm::vec2(0.0f, 0.0f), projectedBottomLeft);
  //float dfzBottomRight = glm::distance(glm::vec2(0.0f, 0.0f), projectedBottomRight);

  float dfzTopLeft = glm::dot(lineUpA, projectedTopLeft);
  float dfzTopRight = glm::dot(lineUpA, projectedTopRight);
  float dfzBottomLeft = glm::dot(lineUpA, projectedBottomLeft);
  float dfzBottomRight = glm::dot(lineUpA, projectedBottomRight);

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
