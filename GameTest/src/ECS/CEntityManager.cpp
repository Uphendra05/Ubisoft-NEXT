#include "stdafx.h"
#include "CEntityManager.h"


namespace Engine
{
    Engine::CEntityManager::CEntityManager()
    {
        mEntityList.reserve(MAX_ENTITIES);

        mEntityVersions.resize(MAX_ENTITIES, 0);
        

        for (Entity entityId = 0; entityId < MAX_ENTITIES; ++entityId) 
        {
            mAvailableEntities.push(entityId);
        }
    }

    Entity Engine::CEntityManager::CreateEntity(EntityMask initialMask)
    {
        if (mEntityList.size() >= MAX_ENTITIES)
        {
            throw std::runtime_error("Maximum number of entities reached.");
        }

        uint32_t index = mAvailableEntities.front();
        mAvailableEntities.pop();

        uint32_t version = mEntityVersions[index];

        Entity newEntity = CreateEntityID(index, version);


        mEntityList.push_back(newEntity);
        mEntityMasks[index] = initialMask;

        return newEntity;
    }

    void Engine::CEntityManager::RemoveEntity(Entity entityId)
    {
        uint32_t index = GetEntityIndex(entityId);

        if (index >= MAX_ENTITIES || GetEntityVersion(entityId) != mEntityVersions[index])
        {
            throw std::runtime_error("Attempted to destroy an invalid entity.");
        }
        ++mEntityVersions[index];
       
        mEntityMasks[index].reset();
        mAvailableEntities.push(index);

        
        std::vector<Entity>::iterator it = std::find(mEntityList.begin(), mEntityList.end(), entityId);

        if (it != mEntityList.end()) 
        {
            mEntityList.erase(it);
        }

    }

    void Engine::CEntityManager::DestroyEntity(Entity entity)
    {
        RemoveEntity(entity);
    }

    const std::vector<Entity>& Engine::CEntityManager::GetEntities() const
    {
        return mEntityList;
    }
     EntityMask CEntityManager::GetEntityMask(Entity entityId) 
    {
        return mEntityMasks[entityId];
    }
}