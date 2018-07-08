#pragma once
#include <glm/glm.hpp>

class Transform
{
public:
  Transform();
  ~Transform();

  void SetPosition(glm::vec3 newPosition);
  void SetRotation(float newRotation);
  void SetScale(glm::vec3 newScale);

  glm::vec3 GetUpVector();
  glm::vec3 GetRightVector();

  glm::vec3& GetPosition();
  float GetRotation();
  glm::vec3& GetScale();

  glm::mat4& BuildTransform();

private:

  

  bool isDirty = true;

  glm::vec3 position_;
  float rotation_;
  glm::vec3 scale_;

  glm::mat4 fullTransform_;
};

