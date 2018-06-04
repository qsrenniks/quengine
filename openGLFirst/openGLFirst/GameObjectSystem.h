#pragma once
#include "IGameplaySystem.h"
#include "IComponent.h"
#include <vector>

class GameObjectSystem : public IGameplaySystem
{


public:
  GameObjectSystem() = default;

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

  using GameObjectList = std::vector<class IGameObject *>;
  using ComponentList = std::vector<class IComponent *>;
  GameObjectList gameObjectRegistry_;
  ComponentList componentRegistry_;
  
};