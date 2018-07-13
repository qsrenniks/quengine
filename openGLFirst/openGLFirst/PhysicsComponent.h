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
  void SetVelocity(const glm::vec2& newVelocity);

  glm::vec2& GetVelocity();


private:
  glm::vec2 velocity_;
  glm::vec2 acceleration_;

  bool frozen_ = false;
};