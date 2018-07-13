#pragma once
#include <vector>
#include <functional>
#include <memory>

template <typename Signature>
class delegate;

template<typename ...Args>
class delegate<void(Args...)>
{
private:

  using CallableFunctionWrapper = std::function<void(Args...)>;

  struct callback
  {
    virtual void operator()(Args... args) = 0;
  };

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

  template<class ObjectInstance>
  struct memberCB : public callback
  {
    memberCB(ObjectInstance* moI, void (ObjectInstance::*mFunc)(Args...))
      : oI(moI)
      , d(mFunc)
    {
      //oI = std::make_unique<ObjectInstance>(*moI);
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
    for (auto a : invocationList)
    {
      (*a)(std::forward<Args>(args)...);
    }
  }

private:
  std::vector<callback*> invocationList;
};
