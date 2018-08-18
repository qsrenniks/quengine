#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/packing.inl>

class Transform
{
public:
  Transform();
  ~Transform();

  void SetPosition(glm::vec2& newPosition);
  void SetPosition(glm::vec2&& newPosition);
  void SetPosition(float x, float y);

  void SetRotation(float newRotation);

  void SetScale(glm::vec2& newScale);
  void SetScale(glm::vec2&& newScale);
  void SetScale(float x, float y);

  bool IsDirty() const;

  const glm::vec2& GetPosition() const;

  float GetRotationD();
  float GetRotationR();
  glm::vec2& GetScale();

  const glm::mat4& BuildTransform();



private:
  //void RecalculateUpAndRightVectors();
  
  //glm::vec2 relativeUpVector_;
  //glm::vec2 relativeRightVector_;

  bool isDirty_ = true;

  glm::vec2 position_;

  float rotation_;
  glm::vec2 scale_;

  glm::mat4 fullTransform_;
};

