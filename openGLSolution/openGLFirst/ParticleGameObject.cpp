#include "stdafx.h"
#include "ParticleGameObject.h"
#include "PhysicsComponent.h"
#include "SpriteComponent.h"

ParticleGameObject::ParticleGameObject()
  : lifetime_(0.0f)
{
  AddComponent<PhysicsComponent>(physicsComponent_);
}

ParticleGameObject::ParticleGameObject(float lifetime)
  : ParticleGameObject()
{
  lifetime_ = lifetime;
}

ParticleGameObject::~ParticleGameObject()
{
}

void ParticleGameObject::SetVelocity(const glm::vec2& newVelocity)
{
  physicsComponent_->SetVelocity(newVelocity);
}

void ParticleGameObject::AddImpulse(const glm::vec2& impulse)
{
  physicsComponent_->AddImpulse(impulse);
}

void ParticleGameObject::SetColor(const glm::vec4& newColor)
{
  sprite_->SetColor(newColor);
}

void ParticleGameObject::SetPosition(const glm::vec2& newPosition)
{
  transform_.SetPosition(newPosition);
}

void ParticleGameObject::Update(float dt)
{

}
