#pragma once
#include "ICommand.h"

class EngineCmd_ExitGame : public ICommand
{
public:
  EngineCmd_ExitGame() = default;
  ~EngineCmd_ExitGame() = default;

  virtual void Execute() override;
};

