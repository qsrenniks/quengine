#include "MemoryModule.h"
#include <iostream>

MemoryModule::MemoryModule(size_t numOfBytes)
  : memHeap_(new size_t[numOfBytes])
{
  
}

MemoryModule::~MemoryModule()
{
  delete[] memHeap_;
}

void MemoryModule::ModuleLoad()
{
  std::cout << "Memory Module Loaded" << std::endl;
}

void MemoryModule::ModuleUnload()
{
  std::cout << "Memory Module Unloaded" << std::endl;
}
