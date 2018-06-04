#pragma once
#include "IGameObject.h"
#include <memory>
class DebugGameObject : public IGameObject
{
public:
  DebugGameObject();
  virtual ~DebugGameObject();

  virtual void Update(float dt) override;

  void WKeyPress();
  void SKeyPress();
  void DKeyPress();
  void AKeyPress();

private:
  class std::unique_ptr<class SpriteComponent> sprite_;
  class std::unique_ptr<class PhysicsComponent> physics_;
};

