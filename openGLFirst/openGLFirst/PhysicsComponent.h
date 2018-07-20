#pragma once
#include <glm/glm.hpp>
#include "IComponent.h"
#include <vector>

struct CollisionOccurence;

struct PhysicalProperties
{
  PhysicalProperties()
    : velocityDecay_(1.0f, 1.0f)
  {
  };

  float GetInverseMass() const;

  float mass_ = 1.0f;
  float bounce_ = 0.8f;
  glm::vec2 velocityDecay_;
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
  void SetPhysicalProperties(float mass, float bounce);
  void SetPhysicalProperties(const PhysicalProperties& physicalProperties);
  
  void SetMass(float mass);
  void SetBounce(float bounce);
  void SetVelocityDecay(float x = 1.0f, float y = 1.0f);

  static void RespondToPhysicalCollision(CollisionOccurence& occurence);

private:
  
  glm::vec2 velocity_;
  glm::vec2 acceleration_;

  float rotationalVelocity_;

  PhysicalProperties physicalProperties_;

  bool simulatePhysics_ = true;

};