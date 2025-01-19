#include "stdafx.h"
#include "ComponentUtils.h"



namespace Engine
{
	FrameCounterComponent* ComponentUtils::mFrameCounter = new FrameCounterComponent();
	FrameCollisionComponent* ComponentUtils::pFrameCol = new FrameCollisionComponent();
	GameStateComponent* ComponentUtils::m_pGameState = new GameStateComponent();
	SystemFactory* ComponentUtils::factory = new SystemFactory();



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
		return m_pGameState;
	}

	SystemFactory* ComponentUtils::GetFactory()
	{
		return factory;
	}

	void ComponentUtils::SetGameState(GameStateComponent* pGameState)
	{
		delete m_pGameState;
		m_pGameState = pGameState;
	}

	void ComponentUtils::Clear()
	{

		delete mFrameCounter;
		delete pFrameCol;
	}

}
