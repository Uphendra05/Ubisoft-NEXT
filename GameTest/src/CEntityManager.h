#pragma once
#ifndef _ENTITYMANAGER_H
#define _ENTITYMANAGER_H


#include <iostream>
#include <vector>
#include "ECSCore.h"



namespace Engine
{
    class EntityManager
    {
    public:

        EntityManager();
        ~EntityManager() {};


        Entity CreateEntity(EntityMask initialMask);
        void RemoveEntity(Entity entityId);
        void DestroyEntity(Entity entity);

        const std::vector<Entity>& GetEntities() const;
         EntityMask GetEntityMask(Entity entityId) ;

         //  TODO: Need some way to look up if the entity has the component I'm looking for. psuedo code bool HasComponent(componentid id){ if id = id return true eles fasle;


    private:

        std::vector<Entity> mEntityList;
        EntityMask mEntityMasks[MAX_ENTITIES];



    };

}
#endif
