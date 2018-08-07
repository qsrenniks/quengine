#include "stdafx.h"
#include "Engine.h"

int main()
{
  //this starts the engine up and gets it ready to deal with input and things
  Engine* engine = Engine::Instance();
  engine->Load();

  //this starts the main game loop. if this returns it means the game is exiting.
  engine->GameLoop();

  //cleans up engine
  Engine::Destroy();
  return 0;
}
