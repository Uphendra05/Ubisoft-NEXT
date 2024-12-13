#pragma once
#ifndef _CSCENE_H
#define _CSCENE_H

#include "CEntityManager.h"
#include "CComponentContainer.h"
#include "../Utilities/BiMap.h"

namespace Engine
{
	class CScene
	{

	public :

        CScene();
        ~CScene();

		Entity CreateEntity(bool addDefault = false);		
		Entity CreateEntity(Entity entityId);		
		void RemoveEntity(Entity entityId);


        template <class T>
        ComponentType GetComponentType()
        {
            static int componentType = mComponentCounter++;
            return componentType;
        }

        // Add new component to entity and return the instance
        template <typename T>
        T* AddComponent(Entity entityId)
        {
            ComponentType componentType = GetComponentType<T>();

            if (mComponentPools.find(componentType) == mComponentPools.end())
            {
                // New component type, make a new pool
                mComponentPools[componentType] = new ComponentPool(sizeof(T));
                mComponentMaps[componentType] = new BiMap<Entity, ComponentId>();
            }

            T* pComponent = Get<T>(entityId);
            if (pComponent != nullptr)
            {
                // Entity already have component, so just return it
                return pComponent;
            }

            // Looks up the component id and mem location in the pool, 
            // and initializes it with placement new
            ComponentId componentId;
            void* mem = mComponentPools[componentType]->Add(componentId);
            pComponent = new (mem) T();

            // Set the relation between the component id and the entity id
            mComponentMaps[componentType]->Add(entityId, componentId);

            // Add component to the entity mask and return the created component
            m_pEntityManager->SetComponent(entityId, componentType);

            return pComponent;
        }

        // Get an entity component using the BiMap and ComponentPool
        template<typename T>
        T* Get(Entity entityId)
        {
            if (mComponentCounter < 0)
            {
                return nullptr;
            }

            ComponentType componentType = GetComponentType<T>();

            if (mComponentPools.find(componentType) == mComponentPools.end())
            {
                return nullptr;
            }

            ComponentId componentId;
            bool hasComponent = mComponentMaps[componentType]->GetByKey(entityId,
                componentId);

            if (!hasComponent)
            {
                return nullptr;
            }

            T* pComponent = static_cast<T*>(mComponentPools[componentType]->Get(componentId));
            return pComponent;
        }

        int GetComponentCount()
        {
            return (int)mComponentMaps.size();
        }

      


	private:

		CEntityManager* mEntityManager;
        std::unordered_map<ComponentType, BiMap<Entity, ComponentId>*> mComponentMaps;
        std::unordered_map<ComponentType, CComponentContainer*>        mComponentPools;
        std::vector<Entity> mEntitiesToDestroy;      

       
        int mComponentCounter;

	};



}
#endif