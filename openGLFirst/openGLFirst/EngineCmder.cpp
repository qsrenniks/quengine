#include "stdafx.h"
#include "EngineCmder.h"
#include "Engine.h"
#include <iostream>

void EngineCmd_ExitGame::Execute()
{
  Engine* instance = Engine::Instance();

  glfwSetWindowShouldClose(instance->GetWindow(), true);
}
