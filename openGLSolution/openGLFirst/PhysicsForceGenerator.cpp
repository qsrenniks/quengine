#include "stdafx.h"
#include "PhysicsForceGenerator.h"
#include <utility>
#include "PhysicsComponent.h"

PhysicsForceGenerator::PhysicsForceGenerator()
{
}


PhysicsForceGenerator::~PhysicsForceGenerator()
{
}

void PhysicsForceGenerator::RegisterForceGenerator(PhysicsComponent* pc, ForceGenerator* fc)
{
  fc->RegisterBody(pc);
  forceRegistry_.emplace_back(std::pair<PhysicsComponent*, ForceGenerator*>(pc, fc));
}

void PhysicsForceGenerator::ApplyForces()
{
  for (std::pair<PhysicsComponent*, ForceGenerator*>& gen : forceRegistry_)
  {
    gen.first->AddForce(gen.second->GenerateForce());
  }
}

glm::vec2 GravityForceGenerator::GenerateForce()
{
  return gravity * body_->GetMass();
}

void ForceGenerator::RegisterBody(PhysicsComponent* phyComp)
{
  body_ = phyComp;
}
