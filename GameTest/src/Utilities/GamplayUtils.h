#pragma once
#ifndef _GAMEPLAYUTILS_H
#define _GAMEPLAYUTILS_H

#include "src/ECS/ECSCore.h"
#include "src/ECS/CScene.h"
#include "src/System/PlayerMovement.h"
#include "src/Utilities/Vector2.h"

namespace Engine
{

	

	class GamplayUtils
	{
	public:

		static Entity CreateECSTEST(CScene* pScene, Vector2 position);

		static Entity CreateBackground(CScene* pScene, Vector2 position);

		static Entity CreatePlayer(CScene* pScene, Vector2 position);

		static Entity CreateCollidable(CScene* pScene, Vector2 position);

		static Entity CreateCollidable2(CScene* pScene, Vector2 position);

		static Entity CreateCamera(CScene* pScene, Vector2 position);



		

	private:

		
	};


}
#endif

