#include "stdafx.h"
#include "GameStateEventSystem.h"
#include "src/Events/GameStateEvent.h"
#include "src/Events/EventBusLocator.hpp"
#include "src/Utilities/ComponentUtils.h"

std::string Engine::GameStateEventSystem::SystemName()
{
    return std::string();
}

void Engine::GameStateEventSystem::Init()
{
}

void Engine::GameStateEventSystem::Start(CScene* pScene)
{
	
}

void Engine::GameStateEventSystem::Update(CScene* pScene, float deltaTime)
{
	GameStateComponent* pState = ComponentUtils::GetGameState();
	if (pState->currState == pState->prevState)
	{
		return;
	}

	StateChanged(pScene, pState->currState);
	pState->prevState = pState->currState;
}

void Engine::GameStateEventSystem::Render(CScene* pScene)
{
}

void Engine::GameStateEventSystem::End(CScene* pScene)
{
}

void Engine::GameStateEventSystem::Cleanup()
{
}

void Engine::GameStateEventSystem::StateChanged(CScene* pScene, const eGameStates& newState)
{
	if (newState == eGameStates::STARTED)
	{
		iEventBus<eGameStateEvents, GameStartedEvent>* pEventBus = EventBusLocator<eGameStateEvents, GameStartedEvent>::Get();

		GameStartedEvent stateEvent = GameStartedEvent();
		stateEvent.pScene = pScene;
		pEventBus->Publish(stateEvent);

		return;
	}
	else if (newState == eGameStates::RUNNING)
	{
		iEventBus<eGameStateEvents, GameRunningEvent>* pEventBus = EventBusLocator<eGameStateEvents, GameRunningEvent>::Get();

		GameRunningEvent stateEvent = GameRunningEvent();
		stateEvent.pScene = pScene;
		pEventBus->Publish(stateEvent);

		return;
	}
	else if (newState == eGameStates::NEWLEVEL)
	{
		iEventBus<eGameStateEvents, GameNewLevelEvent>* pEventBus = EventBusLocator<eGameStateEvents, GameNewLevelEvent>::Get();

		GameNewLevelEvent stateEvent = GameNewLevelEvent();
		stateEvent.pScene = pScene;
		pEventBus->Publish(stateEvent);

		return;
	}
	else if (newState == eGameStates::GAMEOVER)
	{
		iEventBus<eGameStateEvents, GameOverEvent>* pEventBus = EventBusLocator<eGameStateEvents, GameOverEvent>::Get();

		GameOverEvent stateEvent = GameOverEvent();
		stateEvent.pScene = pScene;
		pEventBus->Publish(stateEvent);

		return;
	}

}
