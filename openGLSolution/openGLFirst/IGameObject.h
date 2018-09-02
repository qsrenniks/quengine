#pragma once

#include "IComponent.h"
#include "Delegate.h"
#include "Transform.h"
#include <vector>
#include <string>
#include <rapidjson/document.h>

struct CollisionOccurence;
class SpriteComponent;

class IGameObject
{
public:

  IGameObject();
  IGameObject(const glm::vec2& spawnLocation);
  virtual ~IGameObject();

  //Add Component
  //
  // _Types: Packed parameters for component constructor.
  template <typename Component, class... _Types>
  void AddComponent(Component*& component, _Types&&... _Args)
  {
    //this expands the _Types pack into the parameters passed in to construct the object 
    std::unique_ptr<Component> unique = std::make_unique<Component>(_Args...);

    component = unique.get();

    component->Parent(this);

    component->Register();
    
    componentList_.push_back(std::move(unique));
  }

  template<typename T>
  T* GetComponent()
  {
    T* tempPtr = nullptr;

    for (std::unique_ptr<IComponent>& component : componentList_)
    {
      if ((tempPtr = dynamic_cast<T*>(component.get())) != nullptr)
      {
        break;
      }
    }

    return tempPtr;
  }

  template<>
  SpriteComponent* GetComponent<SpriteComponent>()
  {
    return sprite_;
  }

  //void OnObjectCreated();

  void UpdateGameObject(float dt);
  void DestroyGameObject();
  bool IsMarkedForDestroy();
  //virtual IGameObject* Clone() = 0;
  virtual void Update(float dt) = 0;
  virtual void Serialize(rapidjson::Document& doc);
  virtual void Deserialize(rapidjson::Document& doc);
  void Draw();
  Transform& GetTransform();
  //SpriteComponent* GetSpriteComponent();

  void SetLocation(const glm::vec2& newLocation);
  //Delegate<void(float)>& GetComponentUpdateList();
  //Delegate<void(void)>& GetDrawList();
  //delegate<void(void)>& GetOnObjectCreatedList();
protected:

  Transform transform_;
  SpriteComponent * sprite_;

private:

  //Delegate<void(float)> componentUpdateList_;
  //Delegate<void(void)> componentDrawList_;
  //delegate<void(void)> onObjectCreated_;

  using ComponentList = std::vector<std::unique_ptr<IComponent>>;

  ComponentList componentList_;
  bool markForDestroy_ = false;
};

