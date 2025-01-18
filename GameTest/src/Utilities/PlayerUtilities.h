#pragma once
#ifndef _PLAYERUTILITIES_H
#define _PLAYERUTILITIES_H

#include "src/ECS/SComponentIterator.h"

namespace Engine
{
	class PlayerUtilities
	{

	public:
		static Entity GetPlayerID(CScene* pScene);

		static Entity GetMirroPlayerID(CScene* pScene);

		// Need a way to get player lives sprites as entites

	};
}

#endif
