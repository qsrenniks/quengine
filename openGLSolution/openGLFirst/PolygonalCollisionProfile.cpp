#include "stdafx.h"
#include "PolygonalCollisionProfile.h"
#include "CollisionComponent.h"
#include "IGameObject.h"
#include "CollisionOccurence.h"
#include "SpriteComponent.h"
#include "RigidBodyComponent.h"

//#Bookmark this is where we do the SAT Collision check

//PolygonalCollisionProfile::PolygonalCollisionProfile()
//{
//}
//
//void PolygonalCollisionProfile::IsProfileCollidingWith(NPCollisionProfile* otherProfile) const
//{
  //IGameObject* objectA = collisionComponent_->GetParent();
  //IGameObject* objectB = otherProfile->GetCollisionComponent()->GetParent();

  //assert(objectA != nullptr && objectB != nullptr);

  //SpriteComponent* spriteA = objectA->GetComponent<SpriteComponent>();
  //SpriteComponent* spriteB = objectB->GetComponent<SpriteComponent>();

  ////get meshes
  //Mesh& meshA = spriteA->GetMesh();
  //Mesh& meshB = spriteB->GetMesh();

  //Transform& transformA = spriteA->GetParent()->GetTransform();
  //Transform& transformB = spriteB->GetParent()->GetTransform();

  //const std::vector<glm::vec2>& axisA = meshA.GetAxis();
  //const std::vector<glm::vec2>& axisB = meshB.GetAxis();

  //float overlap = std::numeric_limits<float>::max();
  //glm::vec2 smallestAxis;

  ////sat can return right when an axis is found that it doesnt collide on.
  ////in preperation for a collision
  ////CollisionOccurence collisionOccurence(true);
  ////cehcks the first objects axis to inspect collisoin status.
  //CollisionStatus collisionStatus = PerformAxisProjection(axisA, meshA, meshB, overlap, smallestAxis);

  //if (collisionStatus == CollisionStatus::COLLIDING)
  //{
  //  //checks all object b axis if a collision still has not been detected
  //  collisionStatus = PerformAxisProjection(axisB, meshA, meshB, overlap, smallestAxis);
  //}

  ////if overlap is small enough consider them touching
  //if (overlap < 0.01f)
  //{
  //  collisionStatus = CollisionStatus::TOUCHING;
  //}

  ////sets the objects
  //collOcc.objectA_ = objectA->GetComponent<RigidBodyComponent>();
  //collOcc.objectB_ = objectB->GetComponent<RigidBodyComponent>();
  //collOcc.penetration_ = overlap;
  //collOcc.collisionNormal_ = smallestAxis;
  //collOcc.restitution_ = std::min(collOcc.objectA_->bounce_, collOcc.objectB_->bounce_);

  ////then give it the status of that collision and return;
  //collOcc.collisionStatus_ = collisionStatus;

  //collOcc.objectA_->UpdateCollisionWith(collOcc.objectB_, collisionStatus);
  //collOcc.objectB_->UpdateCollisionWith(collOcc.objectA_, collisionStatus);
//}

//CollisionStatus PolygonalCollisionProfile::IsProfileCollidingWith(CollisionProfile* otherProfile) const
//{
//  return CollisionStatus::INVALID;
//}
//
//CollisionStatus PolygonalCollisionProfile::PerformAxisProjection(const std::vector<glm::vec2>& axisA, Mesh &meshA, Mesh &meshB, float &overlap, glm::vec2 &smallestAxis) const
//{
//  for (const glm::vec2& line : axisA)
//  {
//    Mesh::Projection meshAProjected;
//    Mesh::Projection meshBProjected;
//    meshA.Project(line, meshAProjected);
//    meshB.Project(line, meshBProjected);
//
//    //returns collision status
//    CollisionStatus collStatus = meshAProjected.IsOverlapping(meshBProjected);
//
//    //std::cout << int(collStatus) << std::endl;
//
//    if (collStatus == CollisionStatus::NOT_COLLIDING || collStatus == CollisionStatus::TOUCHING)
//    {
//      return collStatus;
//    }
//    else if (collStatus == CollisionStatus::COLLIDING)
//    {
//      float o = meshAProjected.GetOverlap(meshBProjected);
//
//      if (o < overlap)
//      {
//        overlap = o;
//        smallestAxis = line;
//      }
//    }
//  }
//
//  return CollisionStatus::COLLIDING;
//}
