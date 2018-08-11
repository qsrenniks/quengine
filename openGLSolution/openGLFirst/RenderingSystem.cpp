#include "stdafx.h"
#include "RenderingSystem.h"
#include "Engine.h"
#include "glm/gtc/matrix_transform.hpp"

static const GLuint NumVertices = 6;

static const GLfloat square_vertices[NumVertices][3] =
{
  { -1.0f, 1.0f },
{ 1.0f, -1.0f },
{ 1.0f, 1.0f },
{ -1.0f, 1.0f },
{ -1.0f, -1.0f },
{ 1.0f, -1.0f },
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

  //polygonList_.reserve(1);
  ////create the objects
  glGenBuffers(1, &vbo_);
  glGenVertexArrays(1, &vao_);
  //glCreateBuffers(BufferCount, buffers);

  //putting the memory in the right places
  glBindVertexArray(vao_);
  glBindBuffer(GL_ARRAY_BUFFER, vbo_);
  glBufferData(GL_ARRAY_BUFFER, sizeof(square_vertices), square_vertices, GL_STATIC_DRAW);
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
  glEnableVertexAttribArray(0);

  defaultShader_.use();
}

void RenderingSystem::Unload()
{
  //glDeleteBuffers(1, &vbo_);
  //glDeleteVertexArrays(1, &vao_);
}

void RenderingSystem::DrawSquare(const glm::mat4& transform, const glm::vec4& color, bool wireframeMode)
{
  defaultShader_.setMat4("model", transform);
  defaultShader_.setVec4("aColor", color);
  
  RenderSquare(wireframeMode);
}

void RenderingSystem::DrawSquare(const glm::vec2& location, bool wireframeMode)
{
  defaultShader_.setMat4("model", glm::translate(glm::mat4(1.0f), glm::vec3(location, 0.0f)));
  defaultShader_.setVec4("aColor", glm::vec4(1.0f, 0.0f, 0.0f, 1.0f));

  RenderSquare(wireframeMode);
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

void RenderingSystem::RenderSquare(bool wireframeMode)
{
  defaultShader_.setMat4("projection", Engine::Instance()->GetOrthographicTransform());
  defaultShader_.setMat4("view", Engine::Instance()->GetViewTransform().BuildTransform());

  glBindVertexArray(vao_);

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

//void RenderingSystem::GetShapeVertices(PolygonalShapes shape, int& numOfVerts, const GLfloat* vertices)
//{
//  switch (shape)
//  {
//  case Square_Shape:
//    numOfVerts = NumVertices;
//    vertices = (GLfloat*)square_vertices;
//    break;
//  }
//}
