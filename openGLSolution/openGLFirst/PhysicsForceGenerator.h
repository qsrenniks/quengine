#pragma once
#include <vector>

class PhysicsComponent;
struct ForceGenerator;

class PhysicsForceGenerator
{
public:
  PhysicsForceGenerator();
  ~PhysicsForceGenerator();

  void RegisterForceGenerator(PhysicsComponent* pc, ForceGenerator* fc);

  void ApplyForces();

private:
  std::vector<std::pair<PhysicsComponent*, ForceGenerator*>> forceRegistry_;

};

struct ForceGenerator
{
  virtual glm::vec2 GenerateForce() = 0;

  void RegisterBody(PhysicsComponent* phyComp);

  PhysicsComponent* body_;
};


struct GravityForceGenerator : public ForceGenerator
{
  virtual glm::vec2 GenerateForce() override;

  glm::vec2 gravity = { 0.0f, -9.8f };
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