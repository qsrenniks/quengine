#pragma once
#include "ISystem.h"
#include "Shader.h"

class RenderingSystem : public ISystem
{
public:
  RenderingSystem();
  ~RenderingSystem();


  virtual void Load() override;
  virtual void Unload() override;

  void DrawSquare(const glm::mat4& transform, const glm::vec4& color, bool wireframeMode = false);
  void DrawSquare(const glm::vec2& location, bool wireframeMode = false);
  void DrawSquare(const glm::vec2& location, const glm::vec4& color, float width, float height, bool wireframeMode = false);
  void DrawLine();

  Shader& GetActiveShader();

  //void GetShapeVertices(PolygonalShapes shape, int& numOfVerts, const GLfloat* vertices);

protected:



private:

  void RenderSquare(bool wireframeMode);

  //GLuint vaos[PolygonalShapes::NumOfShapes];
  GLuint vao_;
  GLuint vbo_;
  //GLuint ebo_;

  //GLuint buffers[PolygonalBuffers::BufferCount];
  Shader defaultShader_;
};