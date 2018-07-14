#pragma once
#include "IGameplaySystem.h"
#include "Delegate.h"
#include <glm/glm.hpp>
#include <array>
#include <vector>
#include <stack>
#include <set>
#include <memory>

#include "InputSystem.h"
#include "GameObjectSystem.h"
//class InputSystem;
//class GameObjectSystem;
struct GLFWwindow;
class ICommand;
class Factory;

class Engine
{
public:

  static void Destroy();

                          //current window only necessary for startup
  static Engine* Instance(GLFWwindow* currentWindow = nullptr);

  void ShutDown();

  void AddCommand(ICommand* command);

  void Load();

  void Update(float dt);
  
  //TODO: Remove this from Engine and place in a more camera type system.
  glm::mat4& GetCameraTransform();
  glm::mat4& GetViewTransform();

  void SetWindow(GLFWwindow* window);

  GLFWwindow* GetWindow();
  
  InputSystem* GetInputSystem();
  GameObjectSystem* GetGameObjectSystem();

protected:
  Engine(GLFWwindow* currentWindow);
  ~Engine();

private:

  std::vector<ICommand*> commandStack_;

  static Engine* instance_;

  glm::mat4 cameraTransform_;
  glm::mat4 viewTransform_;

  GLFWwindow* currentWindow_;

  InputSystem inputSystem_;
  GameObjectSystem gameObjectSystem_;
};


