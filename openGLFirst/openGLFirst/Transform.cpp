#include "stdafx.h"
#include "Transform.h"
#include "glm/gtc/matrix_transform.hpp"

#define GLM_ENABLE_EXPERIMENTAL
#include "glm/gtx/rotate_vector.hpp"


Transform::Transform()
  : position_(0.0f, 0.0f)
  , rotation_(0.0f)
  , scale_(1.0f, 1.0f)
  , fullTransform_(1.0f)
{
  RecalculateUpAndRightVectors();
}


Transform::~Transform()
{
}

void Transform::SetPosition(glm::vec2 newPosition)
{
  //oldPosition_ = position_; 
  position_ = newPosition;
  isDirty = true;
}

void Transform::SetRotation(float newRotation)
{
  rotation_ = glm::radians(newRotation);
  RecalculateUpAndRightVectors();
  isDirty = true;
}

void Transform::SetScale(glm::vec2 newScale)
{
  scale_ = newScale;
  isDirty = true;
}

const glm::vec2& Transform::GetUpVector() const
{
  return relativeUpVector_;
}

const glm::vec2& Transform::GetRightVector() const
{
  return relativeRightVector_;
}

glm::vec2& Transform::GetPosition()
{
  return position_;
}

float Transform::GetRotation()
{
  return glm::degrees(rotation_);
}

glm::vec2& Transform::GetScale()
{
  return scale_;
}

glm::mat4& Transform::BuildTransform()
{
  if (isDirty == true)
  {

    auto translation = glm::translate(glm::mat4(1.0f), glm::vec3(position_, 0.0f));
    auto rotation = glm::rotate(glm::mat4(1.0f), rotation_, glm::vec3(0.0f, 0.0f, 1.0f));
    auto scale = glm::scale(glm::mat4(1.0f), glm::vec3(scale_, 0.0f));

    fullTransform_ = translation * rotation * scale ;

    isDirty = false;
  }

  return fullTransform_;
}

//const glm::vec2& Transform::GetOldPosition()
//{
//  return oldPosition_;
//}

void Transform::RecalculateUpAndRightVectors()
{
  glm::vec3 up(0.0f, 1.0f, 0.0f);
  relativeUpVector_ = glm::rotate(up, rotation_, glm::vec3(0.0f, 0.0f, 1.0f));
  
  glm::vec3 right(1.0f, 0.0f, 0.0f);
  relativeRightVector_ = glm::rotate(right, rotation_, glm::vec3(0.0f, 0.0f, 1.0f));
}
