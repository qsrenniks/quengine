#pragma once
#include <glm/glm.hpp>
#include "IComponent.h"

class PhysicsComponent : public IComponent 
{
public: // constants

  static glm::vec2 Gravity;

public:
  PhysicsComponent();

  ~PhysicsComponent() = default;

  //virtual void Draw() override;
  virtual void Update(float dt) override;
  virtual void Draw() override;

  bool GetFrozen();
  void Freeze();
  void UnFreeze();

  void SetAcceleration(const glm::vec2& newAcceleration);
  const glm::vec2& GetAcceleration() const;

  void SetVelocity(const glm::vec2& newVelocity);
  glm::vec2& GetVelocity();

  float GetRotationalVelocity() const;
  void SetRotationalVelocity(float val);

  void SetIsStatic(bool isStatic);
  bool GetIsStatic() const;

private:
  glm::vec2 velocity_;
  glm::vec2 acceleration_;

  float rotationalVelocity_;
  
  //float mass_ = 1.0f;
  //float friction_ = 1.0f;
  //float bounce_ = 1.0f;

  bool isStatic_ = false;
  bool frozen_ = false;
};