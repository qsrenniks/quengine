#pragma once
#include <functional>
#include <list>
//#include <memory>

template <typename Signature>
class Delegate;

//parameter expansion
//This class uses callback classes and functions to achieve a c# like delegate system.
template<typename ...Args>
class Delegate<void(Args...)>
{
private:

  //Holds the function to be called by broadcast.
  using CallableFunctionWrapper = std::function<void(Args...)>;

  //Callback interface that the delegate creates based on the type of the function passed in.

  //ABSTRACT INTERFACE:
  // inherited by nonMemberCB for any function that is not a member function.
  // inherited by memberCB for object instance member function calls.
  struct callback
  {
    virtual ~callback() = default;

    virtual void operator()(Args... args) = 0;
    virtual bool equal(unsigned int pointer) = 0;
  };

  //This is entirely for static function types.
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

    virtual bool equal(unsigned int pointer) override
    {
      return false;
    }

  };

  //This is for member calls to object instances.
  template<class ObjectInstance>
  struct memberCB : public callback
  {
    //Setup the object instance and the member function.
    // moI is the member object instance.
    // mFunc is the function pointer to that member function.
    memberCB(ObjectInstance* moI, void (ObjectInstance::*mFunc)(Args...))
      : oI(moI)
      , d(mFunc)
    {
    };

    //Object Instance type.
    ObjectInstance* oI;
    //This is the type for the object instance member function call.
    void (ObjectInstance::*d)(Args...);

    void operator()(Args... args) override
    {
      //#note if oI is deleted in a frame then this will crash.

      //#note if this crashes because of the problem above, you are not cleaning up memory properly on object destruction.

      //forwarding to preserver move construction
      ((*oI).*d)(std::forward<Args>(args)...);
    };

    //This is an overriden function to support removal of functions and member instances from a delegate.
    virtual bool equal(unsigned int pointer) override
    {
      return pointer == (unsigned int)(oI);
    }

  };

public:
  Delegate()
  {
  };

  ~Delegate()
  {
    //#note Switched it to using smart pointers so this is no longer needed.
    //#note Callback is dynamically allocated and deleted this may cause slow downs later at start up.
    //Deletes the instances of callback in the invocation list.
    for (auto a : invocationList)
    {
      delete a;
    }
  }

  //Static function overload for add function.
  void AddFunction(CallableFunctionWrapper functionCall)
  {
    //invocationList.emplace_back(std::make_unique<nonMemberCB>(functionCall));
    invocationList.emplace_back(new nonMemberCB(functionCall));
  };

  //This is the member function overload for AddFunction.
  template<class ObjectInstance>
  void AddFunction(ObjectInstance* oI, void (ObjectInstance::*mFunc)(Args...))
  {
    //invocationList.emplace_back(std::make_unique<memberCB<ObjectInstance>>(oI, mFunc));
    invocationList.emplace_back(new memberCB<ObjectInstance>(oI, mFunc));
  }

  //#note This function is a terrible fucking design smell.
  //This is the member function for removing callbacks if they are to be removed
  template<class ObjectInstance>
  void RemoveFunction(ObjectInstance* oI, void (ObjectInstance::*mFunc)(Args...))
  {
    //Lambda for the remove_if predicate requirement.k
    //auto lambdaPred = [&](std::unique_ptr<callback>& point) -> bool
    auto lambdaPred = [&](callback* point) -> bool
    {
      //memberCB<ObjectInstance>* mcb = dynamic_cast<memberCB<ObjectInstance>*>(point.get());
      memberCB<ObjectInstance>* mcb = dynamic_cast<memberCB<ObjectInstance>*>(point);

      if (mcb == nullptr)
      {
        return false;
      }
      else
      {
        return mcb->oI == oI && mcb->d == mFunc;
      }
    };
    //Find the object in the list and remove it.
    invocationList.remove_if(lambdaPred);
  }

  //Broadcast the pack to the rest of the invocation list.
  void Broadcast(Args... args)
  {
    if (invocationList.size() == 0)
    {
      return;
    }

    for (auto a : invocationList)
    {
      //This forwards each parameter to the funciton call without copy constructing. 
      (*a)(std::forward<Args>(args)...);
    }
  }

private:
  //#note Made this a list because I wanted quick adding and quick removing from the list.
  // This could change to a vector for simplicity if need be.
  //#note callback* could also be changed to a smart pointer to make resource management easier than it already is.
  std::list<callback*> invocationList;
};
