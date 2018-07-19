#pragma once
#include "CollisionComponent.h"
#include "RigidBodyGameObject.h"

class SpriteComponent;
class PhysicsComponent;
class CollisionComponent;

class DebugGameObject : public RigidBodyGameObject
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

private:

  void OnCollisionUpdate(const CollisionOccurence& otherCollider);
  void OnCollision(const CollisionOccurence& otherCollider);
  void OnExitCollision(const CollisionOccurence& otherCollider);
protected:

};

