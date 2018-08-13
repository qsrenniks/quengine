#include "stdafx.h"
#include "NPCollisionProfile.h"
#include "PolygonalCollisionProfile.h"
#include "CollisionOccurence.h"

NPCollisionProfile::NPCollisionProfile(/*std::initializer_list<glm::vec2> vertexList*/)
{

}

CollisionStatus NPCollisionProfile::IsProfileCollidingWith(CollisionProfile* otherProfile) const
{
  //#Todo remove this statement when ready to debug.
  return CollisionStatus::INVALID;
  
  if (fillerOccurence_ == nullptr)
  {
    return CollisionStatus::INVALID;
  }

  //just to scope the otherProfile name
  {
    NPCollisionProfile* otherProfile = dynamic_cast<NPCollisionProfile*>(otherProfile);

    const VertexList& objectA_Verts = GetVertexList();
    const VertexList& objectB_Verts = otherProfile->GetVertexList();

    //now project them onto axis normals
    //#Todo store these in the collison profiles. 
    //since the vertex list is already seen at runtime these should be calculated then as well and updated when vert list is.
    

  }
}

const NPCollisionProfile::VertexList& NPCollisionProfile::GetVertexList() const
{
  return vertices_;
}

void NPCollisionProfile::SetFillerOccurence(CollisionOccurence& collOcc)
{
  fillerOccurence_ = &collOcc;
}

