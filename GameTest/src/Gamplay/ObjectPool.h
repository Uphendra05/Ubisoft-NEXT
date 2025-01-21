#pragma once
#ifndef _OBJECTPOOL_H
#define _OBJECTPOOL_H


#include "src/ECS/CScene.h"
#include <queue>
#include <functional>


namespace Engine
{
	class ObjectPool
	{


	public:

		void Initialize(CScene* pScene, size_t poolSize, std::function<void(Entity, CScene*)> initializer);
		Entity RequestEntity(CScene* pScene);
		void ReturnEntity(CScene* pScene, Entity entity);

	private:

		std::queue<Entity> mEntityPool; // Pre-allocated pool of entities






	};
}

#endif
