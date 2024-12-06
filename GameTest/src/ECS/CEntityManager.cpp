#include "stdafx.h"
#include "CEntityManager.h"


namespace Engine
{
    Engine::EntityManager::EntityManager()
    {
        mEntityList.reserve(MAX_ENTITIES);

        for (size_t i = 0; i < MAX_ENTITIES; ++i) {
            mEntityMasks[i].reset();
        }
    }

    Entity Engine::EntityManager::CreateEntity(EntityMask initialMask)
    {
        if (mEntityList.size() >= MAX_ENTITIES)
        {
            throw std::runtime_error("Maximum number of entities reached.");
        }

        Entity newEntity = static_cast<Entity>(mEntityList.size());
        mEntityList.push_back(newEntity);
        mEntityMasks[newEntity] = initialMask;
        return newEntity;
    }

    void Engine::EntityManager::RemoveEntity(Entity entityId)
    {
        if (entityId >= mEntityList.size()) 
        {
            throw std::out_of_range("Invalid entity ID.");
        }

       
        mEntityMasks[entityId].reset();        
        Entity lastEntity = mEntityList.back();
        mEntityList[entityId] = lastEntity;
        mEntityList.pop_back();
    }

    void Engine::EntityManager::DestroyEntity(Entity entity)
    {
        RemoveEntity(entity);
    }

    const std::vector<Entity>& Engine::EntityManager::GetEntities() const
    {
        return mEntityList;
    }
     EntityMask EntityManager::GetEntityMask(Entity entityId) 
    {
        return mEntityMasks[entityId];
    }
}