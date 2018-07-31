#pragma once
#include <glm/glm.hpp>
#include "IComponent.h"
#include <vector>

struct CollisionOccurence;
struct ForceGenerator;

struct PhysicalProperties
{
  PhysicalProperties()
    : velocityDecay_(0.999f)
  {
  };

  float GetInverseMass() const;

  float mass_ = 1.0f;
  float bounce_ = 0.8f;
  float velocityDecay_;
};


class PhysicsComponent : public IComponent 
{
public:
  PhysicsComponent();

  ~PhysicsComponent() = default;

  void SetSimulatePhysics(bool simulate);
  bool GetSimulatePhysics();

  //virtual void Draw() override;
  virtual void Update(float dt) override;
  virtual void Draw() override;

  const glm::vec2& GetAcceleration() const;

  const glm::vec2& GetVelocity() const;

  float GetRotationalVelocity() const;
  void SetRotationalVelocity(float val);

  const PhysicalProperties& GetPhysicsProperties() const;
  void SetPhysicalProperties(float mass, float bounce);
  void SetPhysicalProperties(const PhysicalProperties& physicalProperties);
  
  void SetMass(float mass);
  void SetBounce(float bounce);
  void SetVelocityDecay(float x = 1.0f);

  void AddForce(glm::vec2& force);

  void ResetForces();

  void AddImpulse(glm::vec2& impulse);
  
  const glm::vec2& GetCurrentForce();

  void GatherForceGenerators();

  void AddForceGenerator(ForceGenerator* forceGenerator);

  void SetVelocity(const glm::vec2& newVelocity);
  void SetVelocityX(float x);
  void SetVelocityY(float y);  
private:


  void SetAcceleration(const glm::vec2& newAcceleration);

  std::vector<ForceGenerator*> forceGenerators_;

  glm::vec2 forces_;

  glm::vec2 velocity_;
  glm::vec2 acceleration_;

  float rotationalVelocity_;

  PhysicalProperties physicalProperties_;

  bool simulatePhysics_ = true;

};

struct ForceGenerator
{
  virtual glm::vec2 GenerateForce() = 0;

  PhysicsComponent* body_;
};


struct GravityForceGenerator : public ForceGenerator
{
  virtual glm::vec2 GenerateForce() override
  {
    return gravity * body_->GetPhysicsProperties().mass_;
  }

  glm::vec2 gravity = {0.0f, -100.0f};
};

struct PointForceGenerator : public ForceGenerator
{
  PointForceGenerator(float x = 0, float y = 0)
    : pointToPull_(x, y)
  {
  }

  virtual glm::vec2 GenerateForce() override;
  

  glm::vec2 pointToPull_ = { 0.0f, 0.0f };
};