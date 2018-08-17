#include "stdafx.h"
#include "NPCollisionProfile.h"
#include "PolygonalCollisionProfile.h"
#include "CollisionOccurence.h"
#include "CollisionManifold.h"
#include <limits>
#include "CollisionComponent.h"
#include "IGameObject.h"
#include "Transform.h"
#include <utility>

NPCollisionProfile::NPCollisionProfile(std::initializer_list<Vertex> vertexList, std::initializer_list<unsigned int> indices)
  : npMeshProfile_(vertexList, indices)
{
}

CollisionStatus NPCollisionProfile::IsProfileCollidingWith(CollisionProfile* otherProfile) const
{
  //#Todo remove this statement when ready to debug.
  //return CollisionStatus::INVALID;
  
  if (fillerOccurence_ == nullptr)
  {
    return CollisionStatus::INVALID;
  }

  //just to scope the otherProfile name
  {
    NPCollisionProfile* npOtherProfile = dynamic_cast<NPCollisionProfile*>(otherProfile);

    if (npOtherProfile == nullptr)
    {
      return CollisionStatus::INVALID;
    }

    const Mesh& objectA_Mesh = GetMesh();
    const Mesh& objectB_Mesh = npOtherProfile->GetMesh();
    
    //Collect all edge normals into a single list.
    Mesh::EdgeList edgeNormalList;
    edgeNormalList.insert(edgeNormalList.end(), objectA_Mesh.edgeNormals_.cbegin(), objectA_Mesh.edgeNormals_.cend());
    edgeNormalList.insert(edgeNormalList.end(), objectB_Mesh.edgeNormals_.cbegin(), objectB_Mesh.edgeNormals_.cend());

    CollisionManifold objectA_Manifold;
    CollisionManifold objectB_Manifold;

    //now project them onto axis normals
    //#Todo store these in the collison profiles. 
    //since the vertex list is already seen at runtime these should be calculated then as well and updated when vert list is.
  
    Transform& objectATransform = GetCollisionComponent()->GetParent()->GetTransform();
    Transform& objectBTransform = otherProfile->GetCollisionComponent()->GetParent()->GetTransform();

    const glm::mat4& objectA_Mat = objectATransform.BuildTransform();
    const glm::mat4& objectB_Mat = objectBTransform.BuildTransform();

    CollisionStatus currentStatus;

    float minOverlap = std::numeric_limits<float>::max();
    const glm::vec2* smallestEdge = nullptr;

    glm::vec3&& aFirst = objectA_Mat * glm::vec4(glm::vec3(objectA_Mesh.farVertex_.first), 1.0f);
    glm::vec3&& aSecond = objectA_Mat * glm::vec4(glm::vec3(objectA_Mesh.farVertex_.second), 1.0f);

    glm::vec3&& bFirst = objectB_Mat * glm::vec4(glm::vec3(objectB_Mesh.farVertex_.first), 1.0f);
    glm::vec3&& bSecond = objectB_Mat * glm::vec4(glm::vec3(objectB_Mesh.farVertex_.second), 1.0f);

    for (const glm::vec2& edge : edgeNormalList)
    {
      //project the far vertexes onto the edge
      //we have to pass in the transformed vertexes
      objectA_Manifold.ProjectVerticesOntoEdge(aFirst, aSecond, edge);
      objectB_Manifold.ProjectVerticesOntoEdge(bFirst, bSecond, edge);

      currentStatus = objectA_Manifold.IsOverlapping(objectB_Manifold);
      fillerOccurence_->collisionStatus_ = currentStatus;
      //then compare to see if the lines are touching
      
      if (currentStatus == CollisionStatus::NOT_COLLIDING)
      {
        return CollisionStatus::NOT_COLLIDING;
      }
      else if (currentStatus == CollisionStatus::COLLIDING)
      {
        //here we have to calculate normals and overlap
        float aPen = CollisionManifold::GetPenetration(objectA_Manifold, objectB_Manifold);
        if (aPen <= minOverlap)
        {
          minOverlap = aPen;
          smallestEdge = &edge;
        }
      }
    }

    //if it made it this far it means the objects are colliding and the edge and penetration amount should be stored in occ
    fillerOccurence_->penetration_ = minOverlap;
    fillerOccurence_->collisionNormal_ = *smallestEdge;
  }

  fillerOccurence_->collisionStatus_ = CollisionStatus::COLLIDING;
  return CollisionStatus::COLLIDING;
}

const Mesh& NPCollisionProfile::GetMesh() const
{
  return npMeshProfile_;
}

void NPCollisionProfile::SetFillerOccurence(CollisionOccurence& collOcc)
{
  fillerOccurence_ = &collOcc;
}

