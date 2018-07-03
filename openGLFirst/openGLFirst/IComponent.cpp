#include "IComponent.h"
#include "Engine.h"

IComponent::IComponent(ComponentType compType, int z)
  : compType_(compType)
{
}


IComponent::~IComponent()
{
}

void IComponent::Parent(class IGameObject *parent)
{
  parent_ = parent;
}

class IGameObject *IComponent::GetParent() const
{
  return parent_;
}

IComponent::ComponentType IComponent::GetComponentType() const
{
  return compType_;
}
 