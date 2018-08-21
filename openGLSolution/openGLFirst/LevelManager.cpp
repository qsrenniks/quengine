#include "stdafx.h"
#include <sstream>
#include "LevelManager.h"
#include <iostream>

const char* LevelManager::levelConfigLoc = R"(..\data\LevelFiles\lvlconfig.lcon)";
const char* LevelManager::levelLocation = R"(..\data\LevelFiles\)";

LevelManager::LevelManager()
{
  levelConfigFile_.open(levelConfigLoc);

  if (levelConfigFile_.is_open() == false)
  {
    //could not open level config file.
    assert(false);
  }

  SetupLevelFileNames();

  LoadLevel(0);
}

LevelManager::~LevelManager()
{
  levelConfigFile_.close();
}

int LevelManager::GetMaxNumberOfLevels()
{
  return levelFileNames_.size();
}

void LevelManager::LoadLevel(int levelIndex)
{
  std::ifstream currentLevel;
  currentLevel.open(levelFileNames_[levelIndex]);

  if (currentLevel.is_open() == false)
  {
    //cannot open file
    assert(false);
  }


  std::string line;
  while (currentLevel >> line)
  {
    std::stringstream stringStream(line);

    char cInput = 0;
    while (stringStream >> cInput)
    {
      std::cout << cInput;
    }
    std::cout << '\n';
  }

  currentLevel.close();
}

void LevelManager::LevelCharacterParser(char inputChar)
{
  switch (inputChar)
  {
  case 'a':
    break;
  default:
    break;
  }
}

void LevelManager::SetupLevelFileNames()
{
  std::string line;
  while (std::getline(levelConfigFile_, line))
  {
    levelFileNames_.emplace_back(levelLocation + line);
  }
}
