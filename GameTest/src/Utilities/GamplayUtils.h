#pragma once
#ifndef _GAMEPLAYUTILS_H
#define _GAMEPLAYUTILS_H
#include "src/ECS/ECSCore.h"
#include "src/ECS/CScene.h"

#include "src/Utilities/Vector2.h"

namespace Engine
{
	class GamplayUtils
	{
	public:

		static Entity CreateECSTEST(CScene* pScene, Vector2 position);

		static Entity CreateBackground(CScene* pScene, Vector2 position);

		//TODO: should change it later
		static void Update(float dt);
		static void Render();
		static void CleanUp();

	};


}
#endif

