#pragma once
#include <glm/glm.hpp>
#include "IComponent.h"

class PhysicsComponent : public IComponent 
{
public:
  PhysicsComponent();

  ~PhysicsComponent() = default;

  //virtual void Draw() override;
  virtual void Update(float dt) override;
  virtual void Draw() override;


  void SetAcceleration(const glm::vec3& newAcceleration);
  void SetVelocity(const glm::vec3& newVelocity);

  glm::vec3& GetVelocity();

private:
  glm::vec3 velocity_;
  glm::vec3 acceleration_;
};