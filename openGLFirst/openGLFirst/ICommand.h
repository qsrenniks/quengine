#pragma once
class ICommand
{
public:
  ICommand() = default;
  ~ICommand() = default;

  virtual void Execute() = 0;

};

