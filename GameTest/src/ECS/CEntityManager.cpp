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
            mAvailableEntities.push(static_cast<unsigned int>(entityId));
        }
    }

    Entity Engine::CEntityManager::CreateEntity(EntityMask initialMask)
    {
        if (mEntityList.size() >= MAX_ENTITIES)
        {
            throw std::runtime_error("Maximum number of entities reached.");
        }

        Entity newEntity = mAvailableEntities.front();
        mAvailableEntities.pop();

        mEntityMasks[newEntity] = initialMask;
        mEntityList.push_back(newEntity);

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

    void Engine::CEntityManager::SetComponent(Entity entityId, ComponentId componentId)
    {
        if (entityId < 0 || entityId >= MAX_ENTITIES)
        {
            throw std::runtime_error("Invalid entity ID for setting component.");
            return;
        }

        mEntityMasks[entityId].set(componentId, true);
    }

    const std::vector<Entity>& Engine::CEntityManager::GetEntities() const
    {
        return mEntityList;
    }

    EntityMask Engine::CEntityManager::GetEntityMask(Entity entityId) const
    {
        if (entityId < 0 || entityId >= MAX_ENTITIES)
        {
            throw std::runtime_error("Invalid entity ID for setting component.");
            return EntityMask();
        }

        return mEntityMasks[entityId];
    }

    bool Engine::CEntityManager::HasComponents(Entity entityId, const EntityMask& mask) const
    {
        EntityMask entityMask = GetEntityMask(entityId);

        for (int i = 0; i < mask.size(); ++i)
        {
            // If the required component is present in the mask and the entity doesn't have it, return false
            if (mask[i] && !entityMask[i])
            {
                return false;
            }
        }

        // If all required components are found, return true
        return true;


    }

    bool Engine::CEntityManager::HasComponent(Entity entityId, ComponentType componenet) const
    {
        EntityMask mask = GetEntityMask(entityId);
        return mask.test(componenet);
    }


   
}