#pragma once
#include "IGameObject.h"

class PhysicsComponent;

class ParticleGameObject : public IGameObject
{
public:

  ParticleGameObject(float lifetime);
  ParticleGameObject();
  ~ParticleGameObject();

  void SetVelocity(const glm::vec2& newVelocity);
  void AddImpulse(const glm::vec2& impulse);

  void SetColor(const glm::vec4& newColor);
  void SetPosition(const glm::vec2& newPosition);

  virtual void Update(float dt) override;

private:

  float lifetime_ = 0.0f;

  PhysicsComponent* physicsComponent_ = nullptr;
};

