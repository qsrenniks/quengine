#pragma once
#include "ISystem.h"
#include "Shader.h"
#include "Mesh.h"

class RenderingSystem : public ISystem
{
public:
  RenderingSystem();
  ~RenderingSystem();

  virtual void Load() override;
  virtual void Unload() override;

  void DrawSquare(const glm::vec2& location, const glm::vec4& color, float width, float height, bool wireframeMode = false);
  void DrawLine();

  Shader& GetActiveShader();

  //void GetShapeVertices(PolygonalShapes shape, int& numOfVerts, const GLfloat* vertices);

protected:

  //#temporary
  Mesh square;

private:

  void RenderSquare(bool wireframeMode);

  //GLuint vaos[PolygonalShapes::NumOfShapes];
  GLuint vao_;
  GLuint vbo_;
  //GLuint ebo_;

  //GLuint buffers[PolygonalBuffers::BufferCount];
  Shader defaultShader_;
};