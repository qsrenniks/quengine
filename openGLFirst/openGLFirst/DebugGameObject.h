#pragma once
#include "IGameObject.h"

class DebugGameObject : public IGameObject
{
public:
  DebugGameObject();
  virtual ~DebugGameObject();

  virtual void Update(float dt) override;

  virtual IGameObject *Clone() override;
  
  void WKeyPress();
  void SKeyPress();
  void DKeyPress();
  void AKeyPress();

private:
  class std::unique_ptr<class SpriteComponent> sprite_;
  class std::unique_ptr<class PhysicsComponent> physics_;
  class std::unique_ptr<class CollisionComponent> collision_;

};

