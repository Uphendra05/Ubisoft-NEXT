#pragma once

#include "src/ECS/ECSCore.h"
#include "src/ECS/CScene.h"

#include "src/Utilities/Vector2.h"

#include <vector>

namespace Engine
{
	enum eBody
	{
		ACTIVE,
		PASSIVE
	};

	struct sCollisionData
	{
		CScene* pScene;
		Entity entityA;
		Entity entityB;

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