#include "GameObjectSystem.h"
#include "IGameObject.h"

void GameObjectSystem::AddGameObject(IGameObject *gameObject)
{
  gameObjectRegistry_.push_back(gameObject);
}

//bool GameObjectSystem::GameObjectCompare::operator()(IGameObject *lhs, IGameObject *rhs) const
//{
//  return lhs->GetZ() < rhs->GetZ();
//}

GameObjectSystem::~GameObjectSystem()
{
  for (IGameObject* a : gameObjectRegistry_)
  {
    delete a;
  }

  for (IComponent* a : componentRegistry_)
  {
    delete a;
  }
}

//void GameObjectSystem::Draw()
//{
//
//}

void GameObjectSystem::LoadSystem()
{

}

void GameObjectSystem::UpdateSystem(float dt)
{
  std::for_each(gameObjectRegistry_.begin(), gameObjectRegistry_.end(), [&](IGameObject * i) { i->UpdateGameObject(dt); });
}

void GameObjectSystem::UnloadSystem()
{

}