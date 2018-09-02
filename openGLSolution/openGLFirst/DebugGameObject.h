#pragma once
#include "CollisionComponent.h"
#include "IGameObject.h"

class RigidBodyComponent;
class ParticleComponent;

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

  void JKeyPress();
  void KKeyPress();
  void LKeyPress();

  void OnMousePress(glm::vec2 mousePosition);

  //virtual CollisionOccurence GetCollisionOccurence() override;
  void OnCollisionEnter(RigidBodyComponent* otherObject);
  void OnCollisionExit(RigidBodyComponent* otherObject);
protected:

  RigidBodyComponent * rigidBodyComponent_ = nullptr;
  ParticleComponent* particleComponent_ = nullptr;

private:
  
  

};

