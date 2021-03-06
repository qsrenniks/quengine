#include "stdafx.h"
#include "Engine.h"
#include <crtdbg.h>
int main()
{
  _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

  //this starts the engine up and gets it ready to deal with input and things
  Engine* engine = Engine::Instance();
  engine->Load();
  //this starts the main game loop. if this returns it means the game is exiting.
  engine->GameLoop();

  //cleans up engine
  Engine::Destroy();


  return 0;
}
