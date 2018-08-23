#include "stdafx.h"
#include <sstream>
#include "LevelManager.h"
#include <iostream>
#include "GameObjectSystem.h"
#include "Engine.h"

//All game object that spawn through text based level loading go here.
#include "TileGameObject.h"
#include "DebugGameObject.h"

const char* LevelManager::levelConfigLoc = R"(..\data\LevelFiles\lvlconfig.lcon)";
const char* LevelManager::levelLocation = R"(..\data\LevelFiles\)";

LevelManager::LevelManager()
  : startLocation_(0.0f, 0.0f)
{
  levelConfigFile_.open(levelConfigLoc);

  if (levelConfigFile_.is_open() == false)
  {
    //could not open level config file.
    assert(false);
  }

  SetupLevelFileNames();
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

  iterativeLocation_ = startLocation_;

  std::string line;
  while (std::getline(currentLevel, line))
  {
    std::stringstream stringStream(line);

    char cInput = 0;
    while (stringStream.get(cInput))
    {
      //std::cout << cInput;
      LevelCharacterParser(cInput);
    }
    LevelCharacterParser('\n');
    //std::cout << '\n';
  }

  currentLevel.close();
}

void LevelManager::LevelCharacterParser(char inputChar)
{
  const static float hStride = 1.0f;
  const static float vStride = 1.0f;


  GameObjectSystem* objSystem = Engine::Instance()->GetGameObjectSystem();

  switch (inputChar)
  {
  case 'a':
    //spawn objecst here
    objSystem->SpawnGameObjectAtLocation<TileGameObject>(iterativeLocation_);
    break;
  case 'p':
    objSystem->SpawnGameObjectAtLocation<DebugGameObject>(iterativeLocation_);
  default:
    break;
  }

  iterativeLocation_.x += hStride;

  if (inputChar == '\n')
  {
    iterativeLocation_.x = startLocation_.x;
    iterativeLocation_.y -= vStride;
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
