#pragma once
class LevelManager
{
public: //types

  const static char* levelConfigLoc;

public:
  LevelManager();
  ~LevelManager();


private:

  
  unsigned int numberOfLevels_ = 0;
  int currentLevel_ = -1;
  

};

