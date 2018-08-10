#include "stdafx.h"
#include "RenderingSystem.h"
#include "Engine.h"

static const GLuint NumVertices = 6;

static const GLfloat square_vertices[NumVertices][3] =
{
  { -0.5f, 0.5f },
{ 0.5f, -0.5f },
{ 0.5f, 0.5f },
{ -0.5f, 0.5f },
{ -0.5f, -0.5f },
{ 0.5f, -0.5f },
};

RenderingSystem::RenderingSystem()
  : defaultShader_(R"(..\vertexShader.vs)", R"(..\fragmentShader.fs)")
{
}


RenderingSystem::~RenderingSystem()
{
}

void RenderingSystem::Load()
{
  defaultShader_.init();

  //create the objects
  glGenBuffers(BufferCount, buffers);
  glGenVertexArrays(NumOfShapes, vaos);
  //glCreateBuffers(BufferCount, buffers);


  //putting the memory in the right places
  glBindVertexArray(vaos[Square_Shape]);
  glBindBuffer(GL_ARRAY_BUFFER, buffers[Square_Buffer]);
  glBufferData(GL_ARRAY_BUFFER, sizeof(square_vertices), square_vertices, GL_STATIC_DRAW);
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
  glEnableVertexAttribArray(0);
  defaultShader_.use();
}

void RenderingSystem::Unload()
{
  glDeleteBuffers(BufferCount, buffers);
  glDeleteVertexArrays(NumOfShapes, vaos);
}

void RenderingSystem::DrawSquare(const glm::mat4& transform, const glm::vec4& color, bool wireframeMode)
{
  defaultShader_.setMat4("projection", Engine::Instance()->GetOrthographicTransform());
  defaultShader_.setMat4("view", Engine::Instance()->GetViewTransform().BuildTransform());
  defaultShader_.setMat4("model", transform);
  defaultShader_.setVec4("aColor", color);

  glBindVertexArray(vaos[Square_Shape]);

  if (wireframeMode == true)
  {
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
  }
  else
  {
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
  }
  glDrawArrays(GL_TRIANGLES, 0, 6);
}

void RenderingSystem::DrawLine()
{

}

Shader& RenderingSystem::GetActiveShader()
{
  //TODO: make this actually return or use the current shader.
  //objects that are rendering here should be able to change the shader as well.
  return defaultShader_;
}

void RenderingSystem::GetShapeVertices(PolygonalShapes shape, int& numOfVerts, const GLfloat* vertices)
{
  switch (shape)
  {
  case Square_Shape:
    numOfVerts = NumVertices;
    vertices = (GLfloat*)square_vertices;
    break;
  }
}
