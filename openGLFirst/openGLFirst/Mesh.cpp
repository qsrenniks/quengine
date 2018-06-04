#include "Mesh.h"

Mesh::Mesh()
{

}

void Mesh::AddVertexToMesh(float x, float y, float z)
{
  vertices_.push_back(Vertices{ x, y, z });

}

size_t Mesh::GetVerticeSize()
{
  return vertices_.size() * sizeof(Vertices);
}

size_t Mesh::GetIndicesSize()
{
  return indices_.size() * sizeof(unsigned int);
}

void *Mesh::GetVerticeAddress()
{
  return &vertices_[0];
}

void *Mesh::GetIndicesAddress()
{
  return &indices_[0];
}

unsigned int Mesh::GetVAO()
{
  return VAO_;
}

unsigned int Mesh::GetVBO()
{
  return VBO_;
}

unsigned int Mesh::GetEBO()
{
  return EBO_;
}
