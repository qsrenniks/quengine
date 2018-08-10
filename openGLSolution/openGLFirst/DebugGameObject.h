#pragma once
#include "CollisionComponent.h"
#include "IGameObject.h"

class RigidBodyComponent;

class DebugGameObject : public IGameObject
{
public: //public vars

  //static std::string DebugGameObjectName;

public:
  DebugGameObject();
  virtual ~DebugGameObject();

  //virtual IGameObject* Clone() override;
  virtual void Update(float dt) override;

  void WKeyPress();
  void SKeyPress();
  void DKeyPress();
  void AKeyPress();

  //virtual CollisionOccurence GetCollisionOccurence() override;
protected:

  RigidBodyComponent * rigidBodyComponent_ = nullptr;

private:


};

