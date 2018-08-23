#pragma once
#include <fstream>
#include <vector>

class LevelManager
{
public: //types

  const static char* levelConfigLoc;
  const static char* levelLocation;
public:
  LevelManager();
  ~LevelManager();

  int GetMaxNumberOfLevels();

  void LoadLevel(int levelIndex);

private:

  void LevelCharacterParser(char inputChar);

  void SetupLevelFileNames();

  std::vector<std::string> levelFileNames_;
  std::ifstream levelConfigFile_;
  
  glm::vec2 startLocation_;
  glm::vec2 iterativeLocation_;

  int currentLevel_ = -1;
  
  
};

