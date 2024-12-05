#include "stdafx.h"
#include "EntityManager.h"

Entity EntityManager::CreateEntity()
{
	Entity entity = nextEntity++;
	entityList.push_back(entity);
	return entity;
}

void EntityManager::DestroyEntity(Entity entity)
{
	entityList.erase(std::remove(entityList.begin(), entityList.end(), entity), entityList.end()); 
}

const std::vector<Entity>& EntityManager::GetEntities() const
{
	return entityList;
}
