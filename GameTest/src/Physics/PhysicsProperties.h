#pragma once
#ifndef _PHYSICSPROPERTIES_H
#define _PHYSICSPROPERTIES_H

#include "src/ECS/ECSCore.h"
#include "src/ECS/CScene.h"

//*******************************************************************************************
//  PhysicsProperties
//*******************************************************************************************
/* This class holds the struct for collision data. it stores data of collision and triggers an event
* to notify for triggerevent collision enter and exit

 */


namespace Engine
{
	struct sCollisionData
	{
		CScene* pScene = nullptr;
		Entity entityA = -1;
		Entity entityB = -1;

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
#endif