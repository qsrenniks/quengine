#pragma once
class IModule
{
public:
  IModule() = default;
  virtual ~IModule() = default;

  virtual void ModuleLoad() = 0;
  virtual void ModuleUnload() = 0;

private:

protected:

};

