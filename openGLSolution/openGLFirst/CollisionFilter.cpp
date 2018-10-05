#include "stdafx.h"
#include "CollisionFilter.h"


CollisionFilter::CollisionFilter()
{
}

CollisionFilter::~CollisionFilter()
{
}

void CollisionFilter::SetCollisionType(CollisionType collisionType)
{
  collisionTypeInfo_ = collisionType;
}

CollisionType CollisionFilter::GetCollisionType() const
{
  return collisionTypeInfo_;
}

void CollisionFilter::SetCollisionResponseTo(CollisionType collType, CollisionResponseType responseToType)
{
  collisionResponseChannel_[collType] = responseToType;
}

CollisionResponseType CollisionFilter::GetResponseFrom(const CollisionFilter& filterA, const CollisionFilter& filterB)
{
  CollisionType aType = filterA.GetCollisionType();
  CollisionType bType = filterB.GetCollisionType();

  CollisionResponseType aResponseToB = filterA.GetResponseTo(filterB);
  CollisionResponseType bResponseToA = filterB.GetResponseTo(filterA);

  //in order for two objects to collide. their response to each other must be a blocking response.
  //overlapping response just floats through the other object but still relays collision Occurence events like on collision enter and exit.

  //bail if they ignore each other
  if (aResponseToB == CollisionResponseType::Ignore || bResponseToA == CollisionResponseType::Ignore)
  {
    return CollisionResponseType::Ignore;
  }

  if (aResponseToB == bResponseToA)
  {
    return aResponseToB;
  }
  else if (aResponseToB != bResponseToA)
  {
    //if they do not equal then more work is required to determine what the response should be between these objects
    if (aResponseToB == CollisionResponseType::Overlap || bResponseToA == CollisionResponseType::Overlap)
    {
      return CollisionResponseType::Overlap;
    }
  }
  return CollisionResponseType::Ignore;
}

CollisionResponseType CollisionFilter::GetResponseTo(const CollisionFilter& filterOther) const
{
  return collisionResponseChannel_[filterOther.GetCollisionType()];
}
