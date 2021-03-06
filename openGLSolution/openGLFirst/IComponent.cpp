#include "stdafx.h"
#include "IComponent.h"
#include "Engine.h"
#include "IGameObject.h"

IComponent::IComponent(int z)
  : zDraw_(z)
{
}


IComponent::~IComponent()
{
}

void IComponent::Parent(IGameObject* parent)
{
  parent_ = parent;
}

IGameObject* IComponent::GetParent() const
{
  return parent_;
}

void IComponent::Register()
{
  //nothing
}
