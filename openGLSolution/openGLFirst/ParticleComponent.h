#pragma once
#include "IComponent.h"
#include <vector>

class ParticleGameObject;

class ParticleComponent : public IComponent
{
public:
  ParticleComponent();
  ~ParticleComponent();

  void SpawnParticle(const glm::vec4& color, const glm::vec2& location, const glm::vec2& velocity);

  virtual void Update(float dt) override;
  virtual void Draw() override;

  virtual void Serialize(rapidjson::Document& doc) override;
  virtual void Deserialize(rapidjson::Document& doc) override;

  void StartEmitter();
  void StopEmitter();

  //#note if particles per second is zero then spawn rate is one per second
  void SetSpawnRatePerSecond(float particlesPerSecond);

private:
  
  void CreateRandomVelocity(glm::vec2& randomVelocity);

  bool emitterPlaying_ = false;
  float spawnRate_ = 1.0f;
  float spawnTimer_ = 0.0f;

  using ParticleList = std::vector<std::unique_ptr<ParticleGameObject>>;

  ParticleList particleList_;
};

