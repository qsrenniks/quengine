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

  //callback interface that the delegate creates based on the type of the function passed in.
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
      //forwarding to preserver move construction
      ((*oI).*d)(std::forward<Args>(args)...);
    };
  };

public:
  delegate()
  {
  };

  ~delegate()
  {
    //deletes the instances of callback in the invocation list.
    for (auto a : invocationList)
    {
      delete a;
    }
  }

  //static function overload for add function
  void AddFunction(CallableFunctionWrapper functionCall)
  {
    invocationList.push_back(new nonMemberCB(functionCall));
  };

  //member functions // this one is not allowed simply because it takes a reference which could easily go out of scope.
  //template<class ObjectInstance>
  //void AddFunction(ObjectInstance& oI, void (ObjectInstance::*mFunc)(Args...))
  //{
  //  invocationList.push_back(new memberCB<ObjectInstance>(&oI, mFunc));
  //}

  //not dealing with the object instance or checking if its null is worrysome.
  //TODO: clean this up so if you broadcast on a null object it doesnt crash.
  template<class ObjectInstance>
  void AddFunction(ObjectInstance* oI, void (ObjectInstance::*mFunc)(Args...))
  {
    invocationList.push_back(new memberCB<ObjectInstance>(oI, mFunc));
  }

  //broadcast the pack to the rest of the invocation list.
  void Broadcast(Args... args)
  {
    if (invocationList.size() == 0)
    {
      return;
    }

    for (auto a : invocationList)
    {
      //this forwards each parameter to the funciton call without copy constructing. 
      (*a)(std::forward<Args>(args)...);
    }
  }

private:
  std::vector<callback*> invocationList;
};
