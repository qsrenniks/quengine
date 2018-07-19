#pragma once
#include <glm/glm.hpp>
#include "IComponent.h"

struct CollisionOccurence;

struct PhysicalProperties
{
  float mass_ = 1.0f;
  float friction_ = 1.0f;
  float bounce_ = 0.8f;
  float velocityDecay_ = 0.95f;
};

class PhysicsComponent : public IComponent 
{
public: // constants

  static glm::vec2 Gravity;

public:
  PhysicsComponent();

  ~PhysicsComponent() = default;

  void SetSimulatePhysics(bool simulate);
  bool GetSimulatePhysics();

  //virtual void Draw() override;
  virtual void Update(float dt) override;
  virtual void Draw() override;

  void SetAcceleration(const glm::vec2& newAcceleration);
  const glm::vec2& GetAcceleration() const;

  void SetVelocity(const glm::vec2& newVelocity);
  void SetVelocityX(float x);
  void SetVelocityY(float y);
  const glm::vec2& GetVelocity() const;

  float GetRotationalVelocity() const;
  void SetRotationalVelocity(float val);

  const PhysicalProperties& GetPhysicsProperties() const;
  void SetPhysicalProperties(float mass, float friction, float bounce);
  void SetPhysicalProperties(const PhysicalProperties& physicalProperties);
  
  void SetMass(float mass);
  void SetFriction(float friction);
  void SetBounce(float bounce);
  void SetVelocityDecay(float velocityDecay);

  static void RespondToPhysicalCollision(CollisionOccurence& occurence);

  glm::vec2 CalculateEllasticCollision(const PhysicsComponent* physicsComponent, const glm::vec2& mtv);

private:

  glm::vec2 velocity_;
  glm::vec2 acceleration_;

  float rotationalVelocity_;

  PhysicalProperties physicalProperties_;

  bool simulatePhysics_ = true;

};