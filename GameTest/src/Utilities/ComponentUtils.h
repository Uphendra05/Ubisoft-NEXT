#pragma once
#ifndef _COMPONENTUTILS_H
#define _COMPONENTUTILS_H
#include "src/ECS/SComponents.h"
#include "src/Gamplay/SystemFactory.h"

namespace Engine
{
	class ComponentUtils
	{
	public:

		static FrameCounterComponent* GetFrameCounter();
		static FrameCollisionComponent* GetFrameCollision();
		static GameStateComponent* GetGameState();
		static SystemFactory* GetSystemFactory();

		static void SetGameState(GameStateComponent* pGameState);
		static void Clear();

	private:
		static FrameCounterComponent* mFrameCounter;
		static FrameCollisionComponent* pFrameCol;
		static GameStateComponent* mGameState;
		static SystemFactory* mSystemFactory;


	};

}
#endif
