#pragma once
#include <glm/glm.hpp>
#include "IComponent.h"
#include <vector>
#include "PhysicsForceGenerator.h"

struct CollisionOccurence;
struct ForceGenerator;

class PhysicsComponent : public IComponent 
{
public:

  static PhysicsForceGenerator ForceGeneratorRegistry;

  PhysicsComponent();

  ~PhysicsComponent() = default;

  void SetSimulatePhysics(bool simulate);
  bool GetSimulatePhysics();
  virtual void Update(float dt) override;
  virtual void Draw() override;
  const glm::vec2& GetAcceleration() const;
  float GetRotationalVelocity() const;
  void SetRotationalVelocity(float val);
  void SetMass(float mass);
  const glm::vec2& GetForce();
  void AddForce(const glm::vec2& force);
  void ResetForces();
  void AddImpulse(glm::vec2& impulse);
  const glm::vec2& GetForceLastFrame();
  void AddForceGenerator(ForceGenerator* forceGenerator);
  const glm::vec2& GetVelocity() const;
  const glm::vec2& GetVelocityAtFrameStart() const;
  void AddVelocity(const glm::vec2& velToAdd);
  void SetVelocityDecay(float x = 1.0f);
  void SetVelocity(const glm::vec2& newVelocity);
  void SetVelocityX(float x);
  void SetVelocityY(float y);  
  //const glm::vec2& GetAccelerationLastFrame();
  void ZeroOutAcceleration();
  float GetMass();
  float GetInverseMass();
private:

  void SetAcceleration(const glm::vec2& newAcceleration);

  glm::vec2 forces_;
  glm::vec2 lastFrameForce_;
  glm::vec2 velocity_;
  glm::vec2 velocityAtFrameStart_;
  glm::vec2 acceleration_;
  //glm::vec2 lastFrameAcceleration_;
  float rotationalVelocity_;
  float mass_ = 1.0f;
  float inverseMass_ = 1.0f;
  float velocityDecay_ = 1.0f;
  bool simulatePhysics_ = true;
};

