#pragma once
#include "src/Utilities/Vector2.h"
#include "src/ECS/SComponents.h"

#include <vector>
#include "src/ECS/ECSCore.h"

namespace Engine
{
	struct AABB
	{

		Vector2 minXY;
		Vector2 maxXY;


		Vector2 halfSize;  // For quick calculations
		Vector2 center;    // Center of the AABB


		void CalculateBounds(const Transform& transform, const Vector2& size)
		{
			halfSize = size * 0.5f;
			center = transform.position;
			minXY = center - halfSize;
			maxXY = center + halfSize;
		}


	};

}
