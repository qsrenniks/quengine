#include "IGameObject.h"
#include "Engine.h"

IGameObject::IGameObject() 
  : transform_(1.0f)
{
  updateDelegate_.addFunction(this, &IGameObject::Update);
}


IGameObject::~IGameObject()
{
}

void IGameObject::UpdateGameObject(float dt)
{
  ////updateDelegate_.Broadcast(dt);
  //UpdateDelegateList::reverse_iterator start = updateDelegate_.rbegin();
  //
  //for (start; start != updateDelegate_.rend(); start++)
  //{
  //  (**start)(dt);
  //}

  updateDelegate_.broadcast(dt);
}

void IGameObject::DrawGameObject()
{
  drawDelegate_.broadcast();
}

glm::mat4& IGameObject::GetTransform()
{
  return transform_;
}