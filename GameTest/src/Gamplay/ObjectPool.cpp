#include "stdafx.h"
#include "ObjectPool.h"


namespace Engine
{
	void Engine::ObjectPool::Initialize(CScene* pScene, size_t poolSize, std::function<void(Entity, CScene*)> initializer)
	{
		for (size_t i = 0; i < poolSize; ++i)
		{
			Entity entity = pScene->CreateEntity(); // Create a new entity
			initializer(entity, pScene);           // Initialize its components
			mEntityPool.push(entity);              // Add the entity to the pool
		}

	}

	Entity Engine::ObjectPool::RequestEntity(CScene* pScene)
	{
		if (mEntityPool.empty())
		{
			throw std::runtime_error("Cannot Request More Entities from Pool. Resize The Entity Pool");
			return NULL;

		}

		Entity entity = mEntityPool.front();
		mEntityPool.pop();
		return entity;
	}

	void Engine::ObjectPool::ReturnEntity(CScene* pScene, Entity entity)
	{


	}

}
