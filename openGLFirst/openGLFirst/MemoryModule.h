#pragma once
#include "IModule.h"
class MemoryModule :
  public IModule
{
public:
  MemoryModule(size_t numOfBytes);
  virtual ~MemoryModule();

  virtual void ModuleLoad() override;
  virtual void ModuleUnload() override;

private:

  size_t * memHeap_ = nullptr;

protected:

};

