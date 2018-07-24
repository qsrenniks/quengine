#include "stdafx.h"
#include "LoggingSystem.h"


LoggingSystem::LoggingSystem()
{
  
}

LoggingSystem::~LoggingSystem()
{
}

std::ofstream& LoggingSystem::GetLogStream(std::string& logStream)
{
  return logMap_[logStream];
}



void LoggingSystem::AddLogStream(std::string& fileName)
{
  std::string filePath = R"(data\LogFiles\)";
  filePath += fileName;
  filePath += ".log";

  logMap_[fileName] = std::ofstream(filePath);
}

void LoggingSystem::Load()
{
}

void LoggingSystem::Unload()
{
  for (auto itr = logMap_.begin(); itr != logMap_.end(); itr++)
  {
    itr->second.close();
  }
}
