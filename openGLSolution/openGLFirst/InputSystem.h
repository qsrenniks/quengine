#pragma once
#include <vector>
#include <map>
#include <string>
#include "IGameplaySystem.h"
#include "Delegate.h"

struct GLFWwindow;

class InputSystem : public IGameplaySystem
{

public:

  InputSystem();
  //for polymorphic destruction
  virtual ~InputSystem() = default;

  virtual void Load() override;
  virtual void Update(float dt) override;
  virtual void Unload() override;

  void SetWindow(GLFWwindow * window);

  struct KeyActionPair
  {
    KeyActionPair(unsigned int key, std::string actionName, bool consumeInput = false)
      : Key_(key)
      , ActionName_(actionName)
      , consumeInput_(consumeInput)
      , executeDelegate_(true)
    {};

    bool operator==(const std::string& actionName);

    unsigned int Key_;
    bool consumeInput_;
    bool executeDelegate_;
    std::string ActionName_;
  };

  template<class UserClass>
  KeyActionPair& AddInputAction(const std::string& actionName, UserClass* instigatorObject, void (UserClass::*objectAction)(void))
  {
    //#note failed to find action name, maybe its misspelled?
    assert(!(std::find(registeredInputs_.begin(), registeredInputs_.end(), actionName) == registeredInputs_.end()));

    delegateFunctionMap_[actionName].AddFunction(instigatorObject, objectAction);

    auto findKeyActionPair = [&](const KeyActionPair& action) -> bool
    { 
      if (action.ActionName_ == actionName)
      {
        return true;
      }
      return false;
    };

    return *std::find_if(registeredInputs_.begin(), registeredInputs_.end(), findKeyActionPair);
  }

private:

  GLFWwindow* currentWindow_;

  std::vector<KeyActionPair> registeredInputs_;

  //TODO: Make this auto pointers
  using DelegateMap = std::map<std::string, delegate<void(void)>>;

  DelegateMap delegateFunctionMap_;

  void ExecuteDelegate(int i);

};
