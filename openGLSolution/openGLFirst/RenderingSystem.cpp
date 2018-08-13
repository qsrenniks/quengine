#include "stdafx.h"
#include "RenderingSystem.h"
#include "Engine.h"
#include "glm/gtc/matrix_transform.hpp"
#include "Mesh.h"

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

  square.vertices_ = {
    {  0.5f,  0.5f, 0.0f }, //top right
    {  0.5f, -0.5f, 0.0f }, //bottom right
    { -0.5f, -0.5f, 0.0f }, //bottom left
    { -0.5f,  0.5f, 0.0f } //top left
  };

  square.indices_ = { 0, 1, 3, 1, 2, 3 };

  square.SetupMesh();

  defaultShader_.use();
}

void RenderingSystem::Unload()
{
  //glDeleteBuffers(1, &vbo_);
  //glDeleteVertexArrays(1, &vao_);
}

void RenderingSystem::DrawSquare(const glm::vec2& location, const glm::vec4& color, float width, float height, bool wireframeMode /*= false*/)
{
  //#Note construct matrix for shader here and then set it in the current shader
  glm::mat4 squareMatrix;
  //#TODO there might be a better way to construct this. Since I have to deal with this for every object i draw this should be seperated into its 
  //own member function
  glm::mat4 translation = glm::translate(glm::mat4(1.0f), glm::vec3(location, 0.0f));
  //#Note im not sure i need to do this mathematically but oh well.
  glm::mat4 rotation = glm::rotate(glm::mat4(1.0f), 0.0f, glm::vec3(0.0f, 0.0, 1.0f));
  glm::mat4 scale = glm::scale(glm::mat4(1.0f), glm::vec3(width * 2.0f, height * 2.0f, 1.0f));

  squareMatrix = translation * rotation * scale;

  defaultShader_.setMat4("model", squareMatrix);
  defaultShader_.setVec4("aColor", color);

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

  if (wireframeMode == true)
  {
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
  }
  square.Draw();
  //#Note this always sets it back to fill so that the next one coming in can set it to what it want
  glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
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
