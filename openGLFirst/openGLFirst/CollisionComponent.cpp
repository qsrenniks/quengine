#include "stdafx.h"
#include "CollisionComponent.h"
#include "GameObjectSystem.h"
#include "Engine.h"
#include "IGameObject.h"
#include "SpriteComponent.h"

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

SquareCollisionProfile::SquareCollisionProfile(CollisionComponent *component, float width, float height)
  : CollisionProfile(component)
  , width_(width)
  , height_(height)
{
  
}

bool SquareCollisionProfile::IsProfileCollidingWith(CollisionProfile* otherProfile)
{
  glm::vec3 position = component_->GetParent()->GetTransform()[0];
  glm::vec3 otherPosition = otherProfile->GetComponentParent()->GetParent()->GetTransform()[0];

  //do square collision profile check
  //using sat collision check
  SpriteComponent* spriteComponent = component_->GetParent()->GetComponent<SpriteComponent>();
  SpriteComponent* otherSpriteComponent = otherProfile->GetComponentParent()->GetParent()->GetComponent<SpriteComponent>();

  


  return false;
}

CollisionProfile::CollisionProfile(CollisionComponent* component)
  : component_(component)
{
}

CollisionComponent* CollisionProfile::GetComponentParent()
{
  return component_;
}
