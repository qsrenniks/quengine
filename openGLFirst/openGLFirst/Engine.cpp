#include "stdafx.h"
#include "Engine.h"
//#include "GameObjectSystem.h"
#include "InputSystem.h"
#include <glm/gtc/matrix_transform.hpp>
#include "ICommand.h"
#include <memory>
#include <iostream>

Engine* Engine::instance_ = nullptr;

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
  glViewport(0, 0, width, height);
}

Engine::Engine()
  : currentWindow_(nullptr)
  , inputSystem_()
  , gameObjectSystem_()
{
  glfwInit();
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

  currentWindow_ = glfwCreateWindow(900, 900, "LearnOpenGL", nullptr, nullptr);

  if (currentWindow_ == nullptr)
  {
    std::cout << "Failed to create GLFW window" << std::endl;
  }
  glfwMakeContextCurrent(currentWindow_);

  if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
  {
    std::cout << "Failed to initialize GLAD" << std::endl;
  }

  glViewport(0, 0, 900, 900);

  glfwSetFramebufferSizeCallback(currentWindow_, framebuffer_size_callback);

  inputSystem_.SetWindow(currentWindow_);
}

void Engine::AddCommand(ICommand* command)
{
  commandStack_.push_back(command);
}

static float dt = 0.01667f;
void Engine::Update(float)
{
  if (commandStack_.empty() == false)
  {
    auto commandExecuteLambda = [&](ICommand* i) {i->Execute(); };
    std::for_each(commandStack_.begin(), commandStack_.end(), commandExecuteLambda);

    commandStack_.clear();
  }
  
  int state = glfwGetMouseButton(currentWindow_, GLFW_MOUSE_BUTTON_LEFT);
  if (state == GLFW_PRESS /*&& mouseState_ != state*/)
  {
    OnMousePress_.Broadcast(GetMousePosition());
    mouseState_ = state;
  }
  else if(state == GLFW_RELEASE && mouseState_ != state)
  {
    OnMouseRelease_.Broadcast(GetMousePosition());
    mouseState_ = state;
  }

  inputSystem_.Update(dt);
  gameObjectSystem_.Update(dt);
}

void Engine::SetWindow(GLFWwindow* window)
{
  currentWindow_ = window;
}

GLFWwindow* Engine::GetWindow()
{
  return currentWindow_;
}

InputSystem* Engine::GetInputSystem()
{
  return &inputSystem_;
}

GameObjectSystem* Engine::GetGameObjectSystem()
{
  return &gameObjectSystem_;
}

void Engine::TogglePauseGame()
{
  isPaused_ = !isPaused_;

  if (isPaused_)
  {
    dt = 0.0f;
  }
  else
  {
    dt = 0.01667f;
  }

}

const glm::vec2& Engine::GetMousePosition()
{
  double x, y;
  glfwGetCursorPos(currentWindow_, &x, &y);

  int width, height;
  glfwGetWindowSize(currentWindow_, &width, &height);

  int frameWidth, frameHeight;
  glfwGetFramebufferSize(currentWindow_, &frameWidth, &frameHeight);
  //x += width/2;
  //y += height/2;
  
  //mousePosition_.x = x;
  //mousePosition_.y = -y;
  mousePosition_.x = float(x) - float(frameWidth) / 2.0f;
  mousePosition_.y = -(float(y) - float(frameHeight) / 2.0f);

  mousePosition_ = glm::vec4(mousePosition_, 0.0f, 1.0f) * glm::transpose(glm::inverse(viewCamera_.BuildTransform())) ;
  //mousePosition_ = glm::vec4(mousePosition_, 0.0f, 1.0f) * GetOrthographicTransform();
  return mousePosition_;
}

Transform& Engine::GetViewTransform()
{
  return viewCamera_;
}

glm::mat4 Engine::GetOrthographicTransform()
{
  int frameWidth, frameHeight;
  glfwGetFramebufferSize(currentWindow_, &frameWidth, &frameHeight);

  float frameHalfWidth = frameWidth / 2.0f;
  float frameHalfHeight = frameHeight / 2.0f;


  //return glm::ortho(0, width, height, 0, 0, 100);
  return glm::ortho(-frameHalfWidth, frameHalfWidth, -frameHalfHeight, frameHalfHeight, 0.0f, 100.0f);
  //return glm::perspective(glm::radians(45.0f), (float)width / (float)height, 0.1f, 100.0f);
}

Engine::~Engine()
{
  ShutDown();
}

void Engine::Destroy()
{
  delete instance_;
}

Engine* Engine::Instance()
{
  if (instance_ == nullptr)
  {
    instance_ = new Engine();
  }

  return instance_;
}

void Engine::ShutDown()
{
  inputSystem_.Unload();
  gameObjectSystem_.Unload();
}

void Engine::Load()
{
  inputSystem_.Load();
  gameObjectSystem_.Load();

  auto& a = inputSystem_.AddInputAction("PauseGame", this, &Engine::TogglePauseGame);
  a.consumeInput_ = true;
}