#pragma once
#ifndef _GAMELOOP_H
#define _GAMELOOP_H

#include "src/Gamplay/SystemFactory.h"
#include "src/Events/GameStateEvent.h"
#include "src/Events/CollisionEvent.h"
#include "src/Events/iEventBus.h"
#include "src/Utilities/ComponentUtils.h"


namespace Engine
{
	class GameLoop
	{
	public:

		explicit GameLoop()  {};
	    ~GameLoop() {};

		void Start(CScene* pScene);
		void Update(CScene* pScene, float deltaTime);
		void Render(CScene* pScene);
		void End(CScene* pScene);
		void Cleanup();

		

	private :

		void InitGameEvents();

		iEventBus<eGameStateEvents, GameStartedEvent>* m_pEventBusGameStarted = nullptr;
		iEventBus<eGameStateEvents, GameControlsEvent>* m_pEventBusGameControls = nullptr;
		iEventBus<eGameStateEvents, GameRunningEvent>* m_pEventBusGameRunning = nullptr;
		iEventBus<eGameStateEvents, GameNewLevelEvent>* m_pEventBusNewLevel = nullptr;
		iEventBus<eGameStateEvents, GameOverEvent>*    m_pEventBusGameOver = nullptr;


		

	};

}
#endif

