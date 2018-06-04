#pragma once
class IModule
{
public:
  IModule() = default;
  virtual ~IModule() = default;

  virtual void LoadModule() = 0;
  virtual void UnloadModule() = 0;

private:

protected:

};

