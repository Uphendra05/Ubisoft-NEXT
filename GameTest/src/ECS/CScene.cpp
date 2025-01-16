#include "stdafx.h"
#include "CScene.h"
#include "SComponents.h"


namespace Engine
{
	CScene::CScene()
	{
		mComponentCounter = 0;
		mEntityManager = new CEntityManager();
	}
	CScene::~CScene()
	{
		delete mEntityManager;

		using ComponentMapPair = std::pair<ComponentType, BiMap<Entity, ComponentId>*>;
		for (ComponentMapPair componentMap : mComponentMaps)
		{
			delete componentMap.second;
		}

		using ComponentPoolPair = std::pair<ComponentType, CComponentContainer*>;
		for (ComponentPoolPair componentPool : mComponentPools)
		{
			delete componentPool.second;
		}

		

	}

	Entity Engine::CScene::CreateEntity(bool addDefault)
	{
		Entity entityId = mEntityManager->CreateEntity(EntityMask());

		if (addDefault)
		{
			AddComponent<Transform>(entityId); 
		}

		return entityId;
	}

	Entity Engine::CScene::CreateEntity(Entity entityId)
	{
		Entity newEntityId = CreateEntity();
		EntityMask entityMask = mEntityManager->GetEntityMask(entityId);

		for (int componentType = 0; componentType < entityMask.size(); componentType++)
		{
			if (!entityMask[componentType])
			{
				continue;
			}

			// Add component by type
			if (componentType == GetComponentType<Transform>())
			{
				Transform* pOriginal = GetComponent<Transform>(entityId);
				if (pOriginal)
				{
					Transform* pNew = AddComponent<Transform>(newEntityId);
					*pNew = *pOriginal;  // Copy the data
				}
			}
			// Repeat for other components as needed
		}

		return newEntityId;

	}

	void Engine::CScene::RemoveEntity(Entity entityId)
	{
		mEntitiesToDestroy.push_back(entityId);
	}

	int Engine::CScene::GetComponentCount()
	{

		return (int)mComponentMaps.size();
		
	}

	void  Engine::CScene::DestroyEntities()
	{
		for (Entity entityId : mEntitiesToDestroy)
		{
			// Remove all components associated with the entity
			for (auto& componentMap : mComponentMaps)
			{
				// Find the component map for the current entity and remove the components
				BiMap<Entity, ComponentId>* entityComponentMap = componentMap.second;
				if (entityComponentMap->ContainsKey(entityId))
				{
					entityComponentMap->RemoveByKey(entityId);
				}
			}

			// Mark the entity for removal in the entity manager
			mEntityManager->RemoveEntity(entityId);
		}

		// Clear the list of entities to destroy
		mEntitiesToDestroy.clear();
	}

	CEntityManager* Engine::CScene::GetEntityManager()
	{
		return mEntityManager;
	}


}