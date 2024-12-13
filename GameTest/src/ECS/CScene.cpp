#include "stdafx.h"
#include "CScene.h"


namespace Engine
{
	Entity Engine::CScene::CreateEntity(bool addDefault)
	{
		Entity entityId = mEntityManager->CreateEntity(EntityMask());

		if (addDefault)
		{
			AddComponent<TransformComponent>(entityId);  // Example default component
		}

		return entityId;
	}

	Entity Engine::CScene::CreateEntity(Entity entityId)
	{
		return Entity();
	}

	void Engine::CScene::RemoveEntity(Entity entityId)
	{
	}


}