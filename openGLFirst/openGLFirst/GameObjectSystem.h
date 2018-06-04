#pragma once
#include "IGameplaySystem.h"
#include "IComponent.h"
#include <vector>

class GameObjectSystem : public IGameplaySystem
{


public:
  GameObjectSystem()
    : IGameplaySystem(IGameplaySystem::GameObjectSystem)
  {};

  virtual ~GameObjectSystem();
  
  virtual void LoadSystem() override;
  virtual void UpdateSystem(float dt) override;
  virtual void UnloadSystem() override;

  virtual void Draw() override;

  void AddGameObject(class IGameObject *gameObject);

  template<typename T>
  T * CreateComponent()
  {
    T* newComponent = new T;

    componentRegistry_.push_back((void*)newComponent);

    return newComponent;
  }

private:

  //struct GameObjectCompare
  //{
  //  bool operator()(class IGameObject* lhs, class IGameObject* rhs)const;
  //};

  typedef std::vector<class IGameObject *> GameObjectList;
  typedef std::vector<class IComponent *> ComponentList;
  GameObjectList gameObjectRegistry_;
  ComponentList componentRegistry_;
  
};