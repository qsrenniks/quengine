#pragma once
#include "Delegate.h"
#include <glm/glm.hpp>
#include <array>
#include <vector>
#include <string>
#include <memory>

#include "Transform.h"
#include "InputSystem.h"
#include "GameObjectSystem.h"
#include "LoggingSystem.h"
#include "RenderingSystem.h"

//class InputSystem;
//class GameObjectSystem;
//class LoggingSystem;
struct GLFWwindow;
class ICommand;
class Factory;

#ifdef BUILDING_ENGINE
#define ENGINE_DECL __declspec(dllexport)
#else
#define ENGINE_DECL __declspec(dllimport)
#endif

//class ENGINE_DECL std::string;

class Engine
{
public:
  static std::string EngineLog;

  static ENGINE_DECL void Destroy();

  static ENGINE_DECL Engine*  Instance();

  void ShutDown();

  void AddCommand(ICommand* command);

  ENGINE_DECL void Load();

  ENGINE_DECL void Update();

  ENGINE_DECL void GameLoop();
  
  void SetWindow(GLFWwindow* window);

  float GetDeltaTime();

  ENGINE_DECL GLFWwindow* GetWindow();
  
  InputSystem* GetInputSystem();
  GameObjectSystem* GetGameObjectSystem();
  LoggingSystem* GetLoggingSystem();
  RenderingSystem* GetRenderingSystem();

  void TogglePauseGame();
  
  const glm::vec2& GetMousePosition();

  Delegate<void(glm::vec2 mousePosition)> OnMousePress_;
  Delegate<void(glm::vec2 mousePosition)> OnMouseRelease_;
  
  Transform& GetViewTransform();
  glm::mat4 GetOrthographicTransform();
protected:

  Engine();
  ~Engine();

private:
  
  float deltaTime_ = 0.0f;

  int mouseState_ = 0;

  Transform viewCamera_;

  glm::vec2 mousePosition_;

  bool isPaused_ = false;

  std::vector<ICommand*> commandStack_;

  static Engine* instance_;

  GLFWwindow* currentWindow_;

  InputSystem inputSystem_;
  GameObjectSystem gameObjectSystem_;
  LoggingSystem loggingSystem_;
  RenderingSystem renderingSystem_;
};


