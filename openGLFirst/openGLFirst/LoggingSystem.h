#pragma once
#include "IGameplaySystem.h"
#include <fstream>
#include <map>

class LoggingSystem : public ISystem
{
public:
  LoggingSystem();
  virtual ~LoggingSystem();

  std::ofstream& GetLogStream(std::string& logStream);



  void AddLogStream(std::string& fileName);

  virtual void Load() override;
  virtual void Unload() override;

protected:

private:

  std::map<std::string, std::ofstream> logMap_;

};

