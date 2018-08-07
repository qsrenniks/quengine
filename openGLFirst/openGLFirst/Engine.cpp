#include "stdafx.h"
#include "Engine.h"
//#include "GameObjectSystem.h"
#include "InputSystem.h"
#include <glm/gtc/matrix_transform.hpp>
#include "ICommand.h"
#include <memory>
#include <iostream>
#include <chrono>
#include <thread>

Engine* Engine::instance_ = nullptr;

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
  glViewport(0, 0, width, height);
}

Engine::Engine()
  : currentWindow_(nullptr)
  , inputSystem_()
  , gameObjectSystem_()
  , loggingSystem_()
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

void Engine::Update()
{
  std::chrono::system_clock::time_point tickStartTime = std::chrono::system_clock::now();

  //MAIN LOOP
  {
    if (commandStack_.empty() == false)
    {
      auto commandExecuteLambda = [&](ICommand* i) {i->Execute(); };
      std::for_each(commandStack_.begin(), commandStack_.end(), commandExecuteLambda);

      commandStack_.clear();
    }
  
    int state = glfwGetMouseButton(currentWindow_, GLFW_MOUSE_BUTTON_LEFT);
    if (state == GLFW_PRESS && mouseState_ != state)
    {
      OnMousePress_.Broadcast(GetMousePosition());
      mouseState_ = state;
    }
    else if(state == GLFW_RELEASE && mouseState_ != state)
    {
      OnMouseRelease_.Broadcast(GetMousePosition());
      mouseState_ = state;
    }

    if (isPaused_ == true)
    {
      deltaTime_ = 0.0f;
    }

    inputSystem_.Update(GetDeltaTime());
    const static float dt = 0.01667f;
    //gameObjectSystem_.Update(GetDeltaTime());
    gameObjectSystem_.Update(dt);
  }

  std::chrono::system_clock::time_point tickEndTime = std::chrono::system_clock::now();

  std::chrono::duration<double, std::milli> elapsedTime = tickEndTime - tickStartTime;
  
  deltaTime_ = float(elapsedTime.count()) / 1000.0f;

  //gets sixty fps in terms of milliseconds.
  static float SixtyFPS = (1.0f / 60.0f) * 1000.0f;
  if (elapsedTime.count() < SixtyFPS)
  {
    std::chrono::duration<double, std::milli> leftOverTime(SixtyFPS - elapsedTime.count());
    auto delta_ms = std::chrono::duration_cast<std::chrono::milliseconds>(leftOverTime);
    std::this_thread::sleep_for(std::chrono::milliseconds(delta_ms));
    deltaTime_ += delta_ms.count();
  }
  else
  {
    loggingSystem_.GetLogStream(EngineLog) << "Lag Detected" << std::endl;
    std::cout << "lag Detected" << std::endl;
  }

}

void Engine::SetWindow(GLFWwindow* window)
{
  currentWindow_ = window;
}

float Engine::GetDeltaTime()
{
  //delta time is in milliseconds gotta divide to get proper delta time
  return deltaTime_;
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

LoggingSystem* Engine::GetLoggingSystem()
{
  return &loggingSystem_;
}

void Engine::TogglePauseGame()
{
  isPaused_ = !isPaused_;
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

std::string Engine::EngineLog = "EngineLog";

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
  loggingSystem_.GetLogStream(EngineLog) << "--Engine Unloading--" << std::endl;
  
  inputSystem_.Unload();
  gameObjectSystem_.Unload();
  loggingSystem_.Unload();
}

void Engine::Load()
{
  loggingSystem_.Load();
  loggingSystem_.AddLogStream(EngineLog);
  loggingSystem_.AddLogStream(GameObjectSystem::GameObjectSystemLog);

  inputSystem_.Load();
  gameObjectSystem_.Load();

  loggingSystem_.GetLogStream(EngineLog) << "--Engine Loading--" << std::endl;

  auto& a = inputSystem_.AddInputAction("PauseGame", this, &Engine::TogglePauseGame);
  a.consumeInput_ = true;
}