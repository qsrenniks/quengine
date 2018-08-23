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
  //RecalculateUpAndRightVectors();
}


Transform::~Transform()
{
}

void Transform::SetPosition(const glm::vec2& newPosition)
{
  position_ = newPosition;

  isDirty_= true;
}

void Transform::SetPosition(float x, float y)
{
  position_.x = x;
  position_.y = y;

  isDirty_ = true;
}

void Transform::SetPosition(glm::vec2&& newPosition)
{
  SetPosition(std::forward<glm::vec2&>(newPosition));
}

void Transform::SetRotation(float newRotation)
{
  rotation_ = glm::radians(newRotation);

  isDirty_= true;
}

void Transform::SetScale(glm::vec2& newScale)
{
  scale_ = newScale;

  isDirty_ = true;
}

void Transform::SetScale(float x, float y)
{
  scale_.x = x;
  scale_.y = y;

  isDirty_ = true;
}

void Transform::SetScale(glm::vec2&& newScale)
{
  SetScale(std::forward<glm::vec2&>(newScale));
}

bool Transform::IsDirty() const
{
  return isDirty_;
}

//const glm::vec2& Transform::GetUpVector() const
//{
//  return relativeUpVector_;
//}
//
//const glm::vec2& Transform::GetRightVector() const
//{
//  return relativeRightVector_;
//}

const glm::vec2& Transform::GetPosition() const
{
  return position_;
}

float Transform::GetRotationD()
{
  return glm::degrees(rotation_);
}

float Transform::GetRotationR()
{
  return rotation_;
}

glm::vec2& Transform::GetScale()
{
  return scale_;
}

const glm::mat4& Transform::BuildTransform()
{
  if (isDirty_ == true)
  {

    auto translation = glm::translate(glm::mat4(1.0f), glm::vec3(position_, 0.0f));
    auto rotation = glm::rotate(glm::mat4(1.0f), rotation_, glm::vec3(0.0f, 0.0f, 1.0f));
    auto scale = glm::scale(glm::mat4(1.0f), glm::vec3(scale_, 1.0f));

    fullTransform_ = translation * rotation * scale ;
    //fullTransform_ = scale * translation * rotation;
    //fullTransform_ = rotation * scale * translation;

    isDirty_ = false;
  }

  return fullTransform_;
}
