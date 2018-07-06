#include "stdafx.h"
#include "Transform.h"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtx/rotate_vector.hpp"

Transform::Transform()
  : position_(0.0f, 0.0f, 0.0f)
  , rotation_(0.0f)
  , scale_(1.0f, 1.0f, 0.0f)
  , fullTransform_(1.0f)
{
}


Transform::~Transform()
{
}

void Transform::SetPosition(glm::vec3 newPosition)
{
  position_ = newPosition;
  isDirty = true;
}

void Transform::SetRotation(float newRotation)
{
  rotation_ = newRotation;
  isDirty = true;
}

void Transform::SetScale(glm::vec3 newScale)
{
  scale_ = newScale;
  isDirty = true;
}

glm::vec3 Transform::GetUpVector()
{
  glm::vec3 right(1.0f, 0.0f, 0.0f);

  return glm::rotate(right, rotation_, glm::vec3(0.0f, 0.0f, 1.0f));
}

glm::vec3 Transform::GetRightVector()
{
  glm::vec3 up(0.0f, 1.0f, 0.0f);

  return glm::rotate(up, rotation_, glm::vec3(0.0f, 0.0f, 1.0f));
}

glm::vec3& Transform::GetPosition()
{
  return position_;
}

float Transform::GetRotation()
{
  return rotation_;
}

glm::vec3& Transform::GetScale()
{
  return scale_;
}

glm::mat4& Transform::BuildTransform()
{
  if (isDirty == true)
  {

    auto translation = glm::translate(glm::mat4(1.0f), position_);
    auto rotation = glm::rotate(glm::mat4(1.0f), rotation_, glm::vec3(0.0f, 0.0f, 1.0f));
    auto scale = glm::scale(glm::mat4(1.0f), scale_);

    fullTransform_ = translation * scale * rotation;

    isDirty = false;
  }

  return fullTransform_;
}
