#pragma once
#ifndef _CENTITYMANAGER_H
#define _CENTITYMANAGER_H


#include <iostream>
#include <vector>
#include <queue>
#include "ECSCore.h"



namespace Engine
{
    class CEntityManager
    {
    public:

        CEntityManager();
        ~CEntityManager() {};


        Entity CreateEntity(EntityMask initialMask);
        void RemoveEntity(Entity entityId);
        void DestroyEntity(Entity entity);

        void SetComponent(Entity entityId, ComponentId componentId);

        const std::vector<Entity>& GetEntities() const;
        Entity GetEntity(int id);

         EntityMask GetEntityMask(Entity entityId) const ;

         //  TODO: Need some way to look up if the entity has the component I'm looking for. psuedo code bool HasComponent(componentid id){ if id = id return true eles fasle;
        
         //  TODO: Need to look up available entites and should find a way to destroy the entity using entity version number ;

         bool HasComponents(Entity entityId, const EntityMask& mask) const;
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
