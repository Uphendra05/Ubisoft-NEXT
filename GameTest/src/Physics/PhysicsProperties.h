#pragma once

#include "src/ECS/ECSCore.h"
#include "src/ECS/CScene.h"

#include "src/Utilities/Vector2.h"

#include <vector>

namespace Engine
{
	struct sCollisionData
	{
		CScene* pScene = nullptr;
		Entity entityA = -1;
		Entity entityB = -1;
		std::vector<Entity> passiveEntites;

		bool operator==(const sCollisionData& other) const
		{
			return entityA == other.entityA && entityB == other.entityB;
		}

		bool operator<(const sCollisionData& other) const
		{
			return entityB < other.entityB;
		}
	};
}