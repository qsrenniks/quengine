#pragma once
#include <array>

//this is how you tag the objects in the world to behave against others
enum CollisionType : size_t { CT_Default = 0, CT_WorldNonStatic, CT_WorldStatic, CT_Player, CT_Enemy, CT_Bullet, CT_NUMTYPES};

//this is used to detemine the response to another object.
//Blocking is the default behavior
enum class CollisionResponseType : int { Blocking = 0, Ignore, Overlap};

class CollisionFilter
{
public:


  CollisionFilter();

  ~CollisionFilter();

  void SetCollisionType(CollisionType collisionType);

  CollisionType GetCollisionType() const;

  void SetCollisionResponseTo(CollisionType collType, CollisionResponseType responseToType);

  static CollisionResponseType GetResponseFrom(const CollisionFilter& filterA, const CollisionFilter& filterB);

  CollisionResponseType GetResponseTo(const CollisionFilter& filterOther) const;

private:
  
  std::array<CollisionResponseType, CollisionType::CT_NUMTYPES> collisionResponseChannel_;

  CollisionType collisionTypeInfo_ = CollisionType::CT_Default;
};

