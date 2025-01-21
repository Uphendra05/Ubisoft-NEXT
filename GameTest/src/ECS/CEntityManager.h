#pragma once
#ifndef _CENTITYMANAGER_H
#define _CENTITYMANAGER_H


#include <iostream>
#include <vector>
#include <queue>
#include "ECSCore.h"


//*******************************************************************************************
// EntityManager
//*******************************************************************************************
/* This class manages entities in the Engine, since we are following the ECS structure 
* it is necessary to manage the entites and this manager does that job

 */

namespace Engine
{
    class CEntityManager
    {
    public:

        CEntityManager();
        ~CEntityManager() {};


        Entity CreateEntity(EntityMask initialMask); //CreateEntity allows us to create new entites with a new entity mask
        void RemoveEntity(Entity entityId); //RemoveEntity marks all the entites that needs to removed
        void DestroyEntity(Entity entity); //DestroyEntity clears all the marked entites

        void SetComponent(Entity entityId, ComponentId componentId); //SetComponent allows us to set the required components to the created entites

        const std::vector<Entity>& GetEntities() const;
        Entity GetEntity(int id);

        EntityMask GetEntityMask(Entity entityId) const ;

        bool HasComponents(Entity entityId, const EntityMask& mask) const; //checks for components
        bool HasComponent(Entity entityId, ComponentType componenet) const;

        


    private:

        EntityMask mEntityMasks[MAX_ENTITIES];

        std::vector<Entity> mEntityList;
        std::queue<uint64_t> mAvailableEntities;
        std::vector<uint32_t> mEntityVersions;

        inline uint32_t GetEntityIndex(Entity id) 
        {
            return static_cast<uint32_t>((id & INDEX_MASK) >> 32);
        }

        inline uint32_t GetEntityVersion(Entity id) 
        {
            return static_cast<uint32_t>(id & VERSION_MASK);
        }

        inline Entity CreateEntityID(uint32_t index, uint32_t version) 
        {
            return (static_cast<Entity>(index) << 32) | static_cast<Entity>(version);
        }

        inline bool IsEntityValid(Entity entity) 
        {
            uint32_t index = GetEntityIndex(entity);
            uint32_t version = GetEntityVersion(entity);

            return index < MAX_ENTITIES && version == mEntityVersions[index];
        }


    };

}
#endif
