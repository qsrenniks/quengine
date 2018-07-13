#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/packing.inl>

class Transform
{
public:
  Transform();
  ~Transform();

  void SetPosition(glm::vec2 newPosition);
  void SetRotation(float newRotation);
  void SetScale(glm::vec2 newScale);

  const glm::vec2& GetUpVector() const;
  const glm::vec2& GetRightVector() const;

  glm::vec2& GetPosition();
  float GetRotation();
  glm::vec2& GetScale();

  glm::mat4& BuildTransform();


private:
  void RecalculateUpAndRightVectors();
  
  glm::vec2 relativeUpVector_;
  glm::vec2 relativeRightVector_;

  bool isDirty = true;

  glm::vec2 position_;
  float rotation_;
  glm::vec2 scale_;

  glm::mat4 fullTransform_;
};

