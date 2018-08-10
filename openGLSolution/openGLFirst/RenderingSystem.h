#pragma once
#include "ISystem.h"
#include "Shader.h"

enum PolygonalShapes : unsigned int {Square_Shape, NumOfShapes};
enum PolygonalBuffers : unsigned int {Square_Buffer, BufferCount};

class RenderingSystem : public ISystem
{
public:
  RenderingSystem();
  ~RenderingSystem();

  virtual void Load() override;
  virtual void Unload() override;

  void DrawSquare(const glm::mat4& transform, const glm::vec4& color, bool wireframeMode = false);
  void DrawLine();

  Shader& GetActiveShader();

  void GetShapeVertices(PolygonalShapes shape, int& numOfVerts, const GLfloat* vertices);

protected:



private:

  GLuint vaos[PolygonalShapes::NumOfShapes];
  GLuint buffers[PolygonalBuffers::BufferCount];
  Shader defaultShader_;
};