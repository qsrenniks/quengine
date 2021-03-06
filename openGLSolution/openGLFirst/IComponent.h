#pragma once
#include <rapidjson/document.h>
#include <memory>
#include <string>

class IGameObject;

class IComponent 
{
public:
  IComponent(int z = 0);
  virtual ~IComponent();

  virtual void Update(float dt) = 0;
  virtual void Draw() = 0;
  
  virtual void Serialize(rapidjson::Document& doc) = 0;
  virtual void Deserialize(rapidjson::Document& doc) = 0;

  //override this to add new behaviors when parenting a component to a game object
  virtual void Parent(IGameObject* parent);

  IGameObject* GetParent() const;

  //override this to add new behaviors when registering the component with the game object manager.
  virtual void Register();

private:
  IGameObject* parent_ = nullptr;
  int zDraw_ = 0;
};

