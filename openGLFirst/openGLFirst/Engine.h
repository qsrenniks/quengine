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
#include "Transform.h"
//class InputSystem;
//class GameObjectSystem;
struct GLFWwindow;
class ICommand;
class Factory;

class Engine
{
public:

  static void Destroy();

  static Engine* Instance();

  void ShutDown();

  void AddCommand(ICommand* command);

  void Load();

  void Update(float dt);
  
  void SetWindow(GLFWwindow* window);

  GLFWwindow* GetWindow();
  
  InputSystem* GetInputSystem();
  GameObjectSystem* GetGameObjectSystem();

  void TogglePauseGame();
  
  const glm::vec2& GetMousePosition();

  delegate<void(glm::vec2)> OnMousePress_;
  delegate<void(glm::vec2)> OnMouseRelease_;
  
  Transform& GetViewTransform();
  glm::mat4 GetOrthographicTransform();
protected:
  Engine();
  ~Engine();

private:
  
  int mouseState_ = GLFW_RELEASE;

  Transform viewCamera_;

  glm::vec2 mousePosition_;

  bool isPaused_ = false;

  std::vector<ICommand*> commandStack_;

  static Engine* instance_;

  GLFWwindow* currentWindow_;

  InputSystem inputSystem_;
  GameObjectSystem gameObjectSystem_;
};


