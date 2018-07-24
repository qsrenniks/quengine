#pragma once
class ISystem
{
public:
  ISystem();
  virtual ~ISystem();

  virtual void Load() = 0;
  virtual void Unload() = 0;
};

