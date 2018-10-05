#include "stdafx.h"
#include "ParticleComponent.h"
#include "ParticleGameObject.h"
#include "Engine.h"

ParticleComponent::ParticleComponent()
{

}

ParticleComponent::~ParticleComponent()
{

}

void ParticleComponent::SpawnParticle(const glm::vec4& color, const glm::vec2& location, const glm::vec2& velocity)
{
  std::unique_ptr<ParticleGameObject> particleGameObject = std::make_unique<ParticleGameObject>();
  particleGameObject->AddImpulse(velocity);
  particleGameObject->SetColor(color);
  particleGameObject->SetPosition(location);
  particleGameObject->GetTransform().SetScale(glm::vec2(0.25f, 0.25f));
  particleList_.emplace_back(std::move(particleGameObject));
}

void ParticleComponent::Update(float dt)
{

  if (emitterPlaying_)
  {
    spawnTimer_ += dt;

    if (spawnTimer_ >= spawnRate_)
    {
      spawnTimer_ -= spawnRate_;

      //spawn Particles
      //glm::vec2 randomVelocity;
      //CreateRandomVelocity(randomVelocity);
      SpawnParticle(glm::vec4(1.0f, 1.0f, 1.0f, 1.0f), GetParent()->GetTransform().GetPosition(), glm::vec2(0.0f, 0.0f));
    }
  }

  for (auto& gameObject : particleList_)
  {
    gameObject->UpdateGameObject(dt);
  }
}

void ParticleComponent::Draw()
{
  for (auto& gameObject : particleList_)
  {
    gameObject->Draw();
  }
}

void ParticleComponent::Serialize(rapidjson::Document& doc)
{

}

void ParticleComponent::Deserialize(rapidjson::Document& doc)
{

}

void ParticleComponent::StartEmitter()
{
  emitterPlaying_ = true;
}

void ParticleComponent::StopEmitter()
{
  emitterPlaying_ = false;
} 

void ParticleComponent::SetSpawnRatePerSecond(float particlesPerSecond)
{
  if (particlesPerSecond == 0.0f)
  {
    spawnRate_ = 1.0f;
    return;
  }

  spawnRate_ = 1.0f / particlesPerSecond;
}

void ParticleComponent::CreateRandomVelocity(glm::vec2& randomVelocity)
{
  const glm::vec2& mousePos = Engine::Instance()->GetMousePosition();
  randomVelocity = mousePos - GetParent()->GetTransform().GetPosition();
  randomVelocity = glm::normalize(randomVelocity);

  randomVelocity *= 10.0f;
}
