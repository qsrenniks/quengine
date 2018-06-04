#include "Mesh.h"

Mesh::Mesh(float width, float height, const char *vertexShader, const char *fragmentShader, glm::vec4 color, int z)
  : shader_(vertexShader, fragmentShader)
{
  
}
