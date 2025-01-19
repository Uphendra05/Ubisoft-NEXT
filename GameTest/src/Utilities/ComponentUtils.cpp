#include "stdafx.h"
#include "ComponentUtils.h"



namespace Engine
{
	FrameCounterComponent* ComponentUtils::mFrameCounter = new FrameCounterComponent();
	FrameCollisionComponent* ComponentUtils::pFrameCol = new FrameCollisionComponent();
	GameStateComponent* ComponentUtils::mGameState = new GameStateComponent();
	SystemFactory* ComponentUtils::mSystemFactory = new SystemFactory();



	FrameCounterComponent* Engine::ComponentUtils::GetFrameCounter()
	{
		return mFrameCounter;
	}

	FrameCollisionComponent* ComponentUtils::GetFrameCollision()
	{
		return pFrameCol;
	}

	GameStateComponent* ComponentUtils::GetGameState()
	{
		return mGameState;
	}

	SystemFactory* ComponentUtils::GetSystemFactory()
	{
		return mSystemFactory;
	}

	void ComponentUtils::SetGameState(GameStateComponent* pGameState)
	{
		delete mGameState;
		mGameState = pGameState;
	}

	void ComponentUtils::Clear()
	{

		delete mFrameCounter;
		delete pFrameCol;
		delete mGameState;
		delete mSystemFactory;
	}

}
