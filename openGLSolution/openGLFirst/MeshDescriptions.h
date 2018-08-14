#pragma once

#include <initializer_list>
#include "Vertex.h"

//#Todo these should go into some mesh description file.
//header file no less

namespace Shapes
{

  //-------------------- SQUARE -------------------------
  static std::initializer_list<Vertex> Square_Vertices =
  {
    { 0.5f,  0.5f, 0.0f }, //top right
  { 0.5f, -0.5f, 0.0f }, //bottom right
  { -0.5f, -0.5f, 0.0f }, //bottom left
  { -0.5f,  0.5f, 0.0f } //top left
  };

  static std::initializer_list<unsigned int> Square_Indices =
  {
    0, 1, 3, 1, 2, 3
  };



}

