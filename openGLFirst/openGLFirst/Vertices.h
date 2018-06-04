#pragma once

class Vertices
{
public:
  Vertices(float x = 0, float y = 0, float z = 0);
  ~Vertices();

private:
  float x_;
  float y_;
  float z_;
};