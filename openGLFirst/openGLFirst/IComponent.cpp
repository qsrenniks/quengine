#include "stdafx.h"
#include "IComponent.h"
#include "Engine.h"
#include "IGameObject.h"

IComponent::IComponent(std::string& componentName, int z)
  : componentName_(componentName)
  , zDraw_(z)
{
}


IComponent::~IComponent()
{
}

void IComponent::Parent(IGameObject* parent)
{
  parent_ = parent;
}

IGameObject *IComponent::GetParent() const
{
  return parent_;
}

void IComponent::Register()
{
  IGameObject* parent = GetParent();

  parent->GetComponentUpdateList().AddFunction(this, &IComponent::Update);
  parent->GetDrawList().AddFunction(this, &IComponent::Draw);
}
