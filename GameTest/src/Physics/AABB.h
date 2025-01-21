#pragma once
#ifndef _AABB_H
#define _AABB_H

#include "src/Utilities/Vector2.h"
#include "src/ECS/SComponents.h"

#include <vector>
#include "src/ECS/ECSCore.h"

//*******************************************************************************************
//  AABB
//*******************************************************************************************
/* This class holds the struct for creating AABB collision between entities

 */


namespace Engine
{
	struct sAABB
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
#endif