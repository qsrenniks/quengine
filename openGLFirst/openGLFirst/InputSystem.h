#pragma once
#include <vector>
#include <map>
#include <string>
#include "IGameplaySystem.h"
#include "Delegate.h"

class InputSystem : public IGameplaySystem
{

public:

  InputSystem(struct GLFWwindow * window);
  //for polymorphic destruction
  virtual ~InputSystem() override
  {
  };

  virtual void LoadSystem() override;
  virtual void UpdateSystem(float dt) override;
  virtual void UnloadSystem() override;

  //virtual void Draw() override;

  void MoveCameraUp();
  void MoveCameraDown();
  void MoveCameraLeft();
  void MoveCameraRight();

  //template<typename T>
  //void AddDelegateAction(std::string actionName, const T& instigatorObject, void (T::*objectAction)(void))
  //{
  //  DelegateAction delegateAction(instigatorObject, objectAction);

  //  delegateFunctionMap_[actionName] = delegateAction;
  //}

  template<class UserClass>
  void AddInputAction(std::string actionName, UserClass* instigatorObject, void (UserClass::*objectAction)(void))
  {
    delegateFunctionMap_[actionName].AddFunction(instigatorObject, objectAction);
  }

private:
  struct KeyActionPair
  {
    KeyActionPair(unsigned int key, std::string actionName, bool consumeInput = false) 
      : Key_(key)
      , ActionName_(actionName)
      , consumeInput_(consumeInput)
      , executeDelegate_(true)
    {};

    unsigned int Key_;
    bool consumeInput_;
    bool executeDelegate_;
    std::string ActionName_;
  };



  struct GLFWwindow * currentWindow_;

  std::vector<KeyActionPair> registeredInputs_;

  //TODO: Make this auto pointers
  using DelegateMap = std::map<std::string, delegate<void(void)>>;

  DelegateMap delegateFunctionMap_;

  void ExecuteDelegate(int i);

};
