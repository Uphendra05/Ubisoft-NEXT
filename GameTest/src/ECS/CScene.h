#pragma once
#ifndef _CSCENE_H
#define _CSCENE_H

#include "CEntityManager.h"
#include "CComponentContainer.h"
#include "../Utilities/BiMap.h"
#include "App/app.h"


//*******************************************************************************************
// Scene
//*******************************************************************************************
/* This class creates all the entities in the Engine. this class gives all the info needed to 
* create an entity in the world and communicates with the entitymanager for management.

 */


namespace Engine
{
	class CScene
	{

	public :

        CScene();
        ~CScene();

		Entity CreateEntity(bool addDefault = false);		//Actually creates the entity to game world
		Entity CreateEntity(Entity entityId);		//Duplicates the created Entity
		void RemoveEntity(Entity entityId); //Removes Entities
        int GetComponentCount();    
        void DestroyEntities();
        void DestroyAllEntities(); //Destroys everything

        CEntityManager* GetEntityManager();


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
                mComponentPools[componentType] = new CComponentContainer(sizeof(T));
                mComponentMaps[componentType] = new BiMap<Entity, ComponentId>();
            }

            T* pComponent = GetComponent<T>(entityId);
            if (pComponent != nullptr)
            {
                
                return pComponent;                                                              // Entity already have component return it
            }

           
           
            ComponentId componentId;                                                             // Looks up the component id and mem location in the pool, and initializes it with placement new
            void* mem = mComponentPools[componentType]->Add(componentId);
            pComponent = new (mem) T();

            // Set the relation between the component id and the entity id
            mComponentMaps[componentType]->Insert(entityId, componentId);

            // Add component to the entity mask and return the created component
            mEntityManager->SetComponent(entityId, componentType);

            

            return pComponent;
        }

        // Get an entity component using the BiMap and ComponentPool
        template<typename T>
        T* GetComponent(Entity entityId)
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
            bool hasComponent = mComponentMaps[componentType]->GetByKey(entityId,componentId);
              

            if (hasComponent == NULL)
            {
                return nullptr;
            }

            T* pComponent = static_cast<T*>(mComponentPools[componentType]->GetComponent(componentId));
            return pComponent;
        }

      

      


	private:

		CEntityManager* mEntityManager;
        std::unordered_map<ComponentType, BiMap<Entity, ComponentId>*> mComponentMaps;
        std::unordered_map<ComponentType, CComponentContainer*>        mComponentPools;
        std::vector<Entity> mEntitiesToDestroy;
        std::vector<Entity> mDestroyAllEntities;

       
       
        int mComponentCounter;

     

	};



}
#endif