#include "stdafx.h"
#include "GameLoop.h"

#include "src/System/MovementSystem.h"
#include "src/System/RenderSystem.h"
#include "src/System/PlayerMovement.h"
#include "src/System/CollisionSystem.h"
#include "src/System/CameraSystem.h"
#include "src/System/WorldUISystem.h"
#include "src/System/RaycastSystem.h"
#include "src/System/FrameSystem.h"
#include "src/System/PlayerHealthSystem.h"
#include "src/System/ShuffleHoleSystem.h"
#include "src/System/GameStateEventSystem.h"
#include "src/System/LevelSystem.h"
#include "src/Gamplay/LevelOne.h"
#include "src/Gamplay/LevelTwo.h"
#include "src/Gamplay/LevelModifier.h"


#include "src/Events/EventBus.hpp"
#include "src/Events/EventBusLocator.hpp"
#include "src/Utilities/ComponentUtils.h"


namespace Engine
{
	SystemFactory* systemFactory = ComponentUtils::GetSystemFactory();

	void Engine::GameLoop::Start(CScene* pScene)
	{
		InitGameEvents();

	
		systemFactory->CreateSystems<PlayerMovement>();
		systemFactory->CreateSystems<MovementSystem>();
		systemFactory->CreateSystems<RenderSystem>();
		systemFactory->CreateSystems<CollisionSystem>();
		systemFactory->CreateSystems<PlayerHealthSystem>();
		systemFactory->CreateSystems<ShuffleHoleSystem>();
		systemFactory->CreateSystems<WorldUISystem>();
		systemFactory->CreateSystems<FrameSystem>();
		systemFactory->CreateSystems<LevelSystem>();
		systemFactory->CreateSystems<GameStateEventSystem>();
		systemFactory->CreateSystems<LevelOne>();
		systemFactory->CreateSystems<LevelTwo>();
		systemFactory->CreateSystems<LevelModifier>();
	

		// Should this be here ?
		GameStateComponent* pState = ComponentUtils::GetGameState();
		pState->currState = eGameStates::STARTED;
		//systemFactory->Start(pScene);

		//systemFactory.CreateSystems<RaycastSystem>();
		//systemFactory.CreateSystems<CameraSystem>();
	}

	void Engine::GameLoop::Update(CScene* pScene, float deltaTime)
	{
		systemFactory->Update(pScene, deltaTime);

	}

	void Engine::GameLoop::Render(CScene* pScene)
	{
		systemFactory->Render(pScene);

	}

	void Engine::GameLoop::End(CScene* pScene)
	{

		systemFactory->End(pScene);

	}

	void Engine::GameLoop::Cleanup()
	{
		systemFactory->Cleanup();

		delete   m_pEventBusGameStarted;
		delete	m_pEventBusGameRunning;
		delete	m_pEventBusNewLevel;
		delete	m_pEventBusGameOver;
		delete  systemFactory;

	}

	

	void Engine::GameLoop::InitGameEvents()
	{
		m_pEventBusGameStarted = new EventBus<eGameStateEvents, GameStartedEvent>();
		m_pEventBusGameRunning = new EventBus<eGameStateEvents, GameRunningEvent>();
		m_pEventBusNewLevel = new EventBus<eGameStateEvents, GameNewLevelEvent>();
		m_pEventBusGameOver = new EventBus<eGameStateEvents, GameOverEvent>();

		EventBusLocator<eGameStateEvents, GameStartedEvent>::Set(m_pEventBusGameStarted);
		EventBusLocator<eGameStateEvents, GameRunningEvent>::Set(m_pEventBusGameRunning);
		EventBusLocator<eGameStateEvents, GameNewLevelEvent>::Set(m_pEventBusNewLevel);
		EventBusLocator<eGameStateEvents, GameOverEvent>::Set(m_pEventBusGameOver);

	}

}
