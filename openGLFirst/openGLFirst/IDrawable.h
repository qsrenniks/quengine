#pragma once

class IDrawable
{
public:

  IDrawable(unsigned int z = 0);

  virtual void Draw() = 0;

private:
  unsigned int z_;

};