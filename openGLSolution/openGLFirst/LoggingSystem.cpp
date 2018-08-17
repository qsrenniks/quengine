#include "stdafx.h"
#include "LoggingSystem.h"
#include <iostream>

LoggingSystem::LoggingSystem()
{
  
}

LoggingSystem::~LoggingSystem()
{
}

void LoggingSystem::PrintToLog(const std::string& fileName, std::string& output)
{
  logCollection_[fileName] << output.data();
}

std::ofstream& LoggingSystem::GetLogStream(const std::string& logStream)
{
  return logCollection_[logStream];
}

void LoggingSystem::AddLogStream(const std::string& fileName)
{
  logCollection_[fileName] = std::ofstream(fileName);
}

void LoggingSystem::Load()
{
}

void LoggingSystem::Unload()
{
  //#Todo close all streams when the game unloads

  for (auto itr = logCollection_.begin(); itr != logCollection_.end(); itr++)
  {
    itr->second.close();
  }
}
