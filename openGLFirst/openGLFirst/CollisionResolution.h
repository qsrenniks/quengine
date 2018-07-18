#pragma once
#include <map>
#include <functional>

struct CollisionOccurence;
class CollisionComponent;
class PhysicsComponent;
//
////
//// Collison Response class, derive off of this in order to create custom response behaviors to collisions of any kind
////
//struct CollisionResponse
//{
//public:
//  CollisionResponse() = default;
//  virtual ~CollisionResponse() = default;
//
//  virtual void Respond(const CollisionOccurence& occurence);
//
//  void SetCollisionComponent(CollisionComponent* collisionComponent);
//  CollisionComponent* GetCollisionComponent() const;
//
//protected:
//
//  CollisionComponent * collisionComponent_;
//
//};
//
//struct PhysicalResponse : public CollisionResponse
//{
//public:
//  PhysicalResponse(PhysicsComponent* physicsComponent, bool isStatic = false, float mass = 1.0f, float friction = 1.0f, float bounce = 1.0f);
//  virtual ~PhysicalResponse();
//
//  virtual void Respond(const CollisionOccurence& occurence) override;
//
//private:
//  PhysicsComponent * physicsComponent_ = nullptr;
//
//  float mass_ = 1.0f;
//  float friction_ = 1.0f;
//  float bounce_ = 1.0f;
//
//  bool isStatic_ = false;
//};
//
//struct DebugResponse : public CollisionResponse
//{
//public:
//  DebugResponse() = default;
//  virtual ~DebugResponse() = default;
//
//  virtual void Respond(const CollisionOccurence& occurence) override;
//};

class CollisionResolution
{
public:
  CollisionResolution();
  ~CollisionResolution();

  void DetermineResolution(const CollisionOccurence& occurence);

private:

  using ObjectPair = std::pair<std::string, std::string>;
  using Response = std::function<void(const CollisionOccurence& occurence)>;

  std::map<ObjectPair, Response> collisionMap_;
};

