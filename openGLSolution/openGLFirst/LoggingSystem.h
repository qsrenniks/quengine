#pragma once
#include "IGameplaySystem.h"
#include <fstream>
#include <map>

class LoggingSystem : public ISystem
{
public:
  LoggingSystem();
  virtual ~LoggingSystem();


  void PrintToLog(const std::string& fileName, std::string& output);
  std::ofstream& GetLogStream(const std::string& logStream);
  void AddLogStream(const std::string& fileName);

  virtual void Load() override;
  virtual void Unload() override;

protected:

private:

  std::map<std::string, std::ofstream> logCollection_;

};

