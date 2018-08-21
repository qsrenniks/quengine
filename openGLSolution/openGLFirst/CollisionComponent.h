#pragma once
#include "IComponent.h"
#include <vector>

class CollisionComponent;
class Mesh;
struct CollisionOccurence;
class NPCollisionProfile;
class BPCollisionProfile;

enum class CollisionStatus : int;

//
// This is the definition of the collision component.
//
class CollisionComponent : public IComponent
{
public:
  CollisionComponent(NPCollisionProfile* npCollisionProfile, BPCollisionProfile* bpCollisionProfile);
  ~CollisionComponent();
 
  virtual void Update(float dt) override;
  virtual void Draw() override;

  //virtual void Parent(IGameObject* parent) override;

  virtual void Register() override;

  NPCollisionProfile* GetNPCollisionProfile() const;
  BPCollisionProfile* GetBPCollisionProfile() const;

  CollisionStatus IsNPCollidingWith(CollisionComponent* otherCollider, CollisionOccurence& collOcc);
  CollisionStatus IsBPCollidingWith(CollisionComponent* otherCollider);


  virtual void Serialize(rapidjson::Document& doc) override;
  virtual void Deserialize(rapidjson::Document& doc) override;

private:

  NPCollisionProfile* npCollisionProfile_ = nullptr;
  BPCollisionProfile* bpCollisionProfile_ = nullptr;
};

