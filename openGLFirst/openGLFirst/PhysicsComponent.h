#pragma once
#include <glm/glm.hpp>
#include "IComponent.h"

class PhysicsComponent : public IComponent 
{
public:
  PhysicsComponent();

  ~PhysicsComponent() = default;

  virtual void Draw() override;
  virtual void Update(float dt) override;

  void SetAcceleration(const glm::vec3& newAcceleration);
  void SetVelocity(const glm::vec3& newVelocity);
private:
  glm::vec3 velocity_;
  glm::vec3 acceleration_;

  glm::vec3 objectGravity_;
};