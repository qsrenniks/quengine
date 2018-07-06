#include "stdafx.h"
#include "CollisionComponent.h"
#include "GameObjectSystem.h"
#include "Engine.h"
#include "IGameObject.h"
#include "SpriteComponent.h"
#include "glm/vec2.hpp"
#include <iostream>

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
  glm::vec3 position = component_->GetParent()->GetTransform().GetPosition();
  glm::vec3 otherPosition = otherProfile->GetComponentParent()->GetParent()->GetTransform().GetPosition();

  //do square collision profile check
  //using sat collision check
  SpriteComponent* spriteComponent = component_->GetParent()->GetComponent<SpriteComponent>();
  SpriteComponent* otherSpriteComponent = otherProfile->GetComponentParent()->GetParent()->GetComponent<SpriteComponent>();

  Mesh& thisMesh = spriteComponent->GetMesh();
  Mesh& otherMesh = otherSpriteComponent->GetMesh();

  bool intersecting = false;

  for (int i = 0; i < 4; i++)
  {
    glm::vec2 line;

    //do this with axis of the second cube

    //switch (i)
    //{
    //case 0:
    //  line = glm::vec2(1.0f, 0.0f); //east
    //  break;
    //case 1:
    //  line = glm::vec2(0.0f, 1.0f); //north
    //  break;
    //case 2:
    //  line = glm::vec2(0.5f, 0.5f); //northeast
    //  break;
    //case 3:
    //  line = glm::vec2(0.5f, -0.5f); //southeast
    //  break;
    //}


    glm::vec2 lineMidPoint = line / 2.0f;
    glm::normalize(line);

    float midPoint = glm::dot(lineMidPoint, line);

    float thisDotPosition = 0;
    float otherDotPosition = 0;
    for (int thisVert = 0; thisVert < 4; thisVert++)
    {
      glm::vec2 thisVertPos = thisMesh.GetVertPos((Mesh::MeshCorner)thisVert);
      thisDotPosition = glm::dot(line, thisVertPos);

      glm::vec2 otherVertPos = otherMesh.GetVertPos((Mesh::MeshCorner)thisVert);
      otherDotPosition = glm::dot(line, otherVertPos);

      if ((thisDotPosition >= midPoint && otherDotPosition <= midPoint) || (thisDotPosition <= midPoint && otherDotPosition >= midPoint))
      {
        intersecting = false;
      }
      else
      {
        intersecting = true;
      }
    }

    if (intersecting == false)
    {
      break;
    }
  }

  return intersecting;
}

CollisionProfile::CollisionProfile(CollisionComponent*& component)
  : component_(component)
{
}

CollisionComponent* CollisionProfile::GetComponentParent()
{
  return component_;
}
