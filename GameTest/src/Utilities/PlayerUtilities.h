#pragma once
#ifndef _PLAYERUTILITIES_H
#define _PLAYERUTILITIES_H

#include "src/ECS/SComponentIterator.h"
#include "src/Gamplay/Enums.h"
namespace Engine
{
	class PlayerUtilities
	{

	public:
		static Entity GetPlayerID(CScene* pScene);

		static size_t PointStreaks(size_t strokes, size_t multiplier,eGameStreaks mGameStreaks );

	private:

		static size_t CalculateResult(size_t strokes, size_t points, size_t multiplier);
	};
}

#endif
