#pragma once
#include <vector>
#include <functional>
#include <memory>

template <typename Signature>
class delegate;

//parameter expansion
template<typename ...Args>
class delegate<void(Args...)>
{
private:

  //mainly for the non member function callbacks
  using CallableFunctionWrapper = std::function<void(Args...)>;

  struct callback
  {
    virtual void operator()(Args... args) = 0;
  };

  //this is entirely for static calls
  struct nonMemberCB : public callback
  {
    nonMemberCB(CallableFunctionWrapper nmFunc)
      : func(nmFunc)
    {};

    CallableFunctionWrapper func;

    void operator()(Args... args) override
    {
      func(std::forward<Args>(args)...);
    };
  };

  //this is for member calls to object instnaces
  template<class ObjectInstance>
  struct memberCB : public callback
  {
    //setup the object instance and the member function
    memberCB(ObjectInstance* moI, void (ObjectInstance::*mFunc)(Args...))
      : oI(moI)
      , d(mFunc)
    {
    };

    ObjectInstance* oI;
    void (ObjectInstance::*d)(Args...);

    void operator()(Args... args) override
    {
      ((*oI).*d)(std::forward<Args>(args)...);
    };
  };

public:
  delegate()
  {
  };

  ~delegate()
  {
    for (auto a : invocationList)
    {
      delete a;
    }
  }

  //template <typename T>
  void AddFunction(CallableFunctionWrapper functionCall)
  {
    invocationList.push_back(new nonMemberCB(functionCall));
  };

  //member functions
  template<class ObjectInstance>
  void AddFunction(ObjectInstance& oI, void (ObjectInstance::*mFunc)(Args...))
  {
    invocationList.push_back(new memberCB<ObjectInstance>(&oI, mFunc));
  }

  template<class ObjectInstance>
  void AddFunction(ObjectInstance* oI, void (ObjectInstance::*mFunc)(Args...))
  {
    invocationList.push_back(new memberCB<ObjectInstance>(oI, mFunc));
  }
  void Broadcast(Args... args)
  {
    if (invocationList.size() == 0)
    {
      return;
    }

    for (auto a : invocationList)
    {
      (*a)(std::forward<Args>(args)...);
    }
  }

private:
  std::vector<callback*> invocationList;
};
