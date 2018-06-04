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

void MemoryModule::LoadModule()
{
  std::cout << "Memory Module Loaded" << std::endl;
}

void MemoryModule::UnloadModule()
{
  std::cout << "Memory Module Unloaded" << std::endl;
}
