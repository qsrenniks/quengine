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
  
  void OnMousePress(glm::vec2 mousePosition);

  //virtual CollisionOccurence GetCollisionOccurence() override;
  void OnCollisionEnter(RigidBodyComponent* otherObject);
  void OnCollisionExit(RigidBodyComponent* otherObject);
protected:

  float health = 69.0f;

  RigidBodyComponent * rigidBodyComponent_ = nullptr;

private:
  
  

};

