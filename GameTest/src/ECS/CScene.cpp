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

		for (std::unordered_map<ComponentType, BiMap<Entity, ComponentId>*>::iterator it = mComponentMaps.begin(); it != mComponentMaps.end(); ++it)
		{
			delete it->second; 
		}
		mComponentMaps.clear();

		for (std::unordered_map<ComponentType, CComponentContainer*>::iterator it = mComponentPools.begin(); it != mComponentPools.end(); ++it)
		{
			delete it->second;
		}
		mComponentPools.clear();

		

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
				Transform* pOriginal = Get<Transform>(entityId);
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


}