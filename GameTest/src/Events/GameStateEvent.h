#pragma once

#include "Event.hpp"

#include "src/ECS/CScene.h"

namespace Engine
{
	enum eGameStateEvents
	{
		GAME_STARTED,
		GAME_RUNNING,
		GAME_NEWLEVEL,
		GAME_OVER
	};

	class GameStartedEvent : public Event<eGameStateEvents>
	{
	public:
		GameStartedEvent() :
			Event<eGameStateEvents>(eGameStateEvents::GAME_STARTED, "GameStarted") {};
		virtual ~GameStartedEvent() {};

		CScene* pScene = nullptr;
	};

	class GameRunningEvent : public Event<eGameStateEvents>
	{
	public:
		GameRunningEvent() : Event<eGameStateEvents>(eGameStateEvents::GAME_RUNNING, "GameRunning") {};
		virtual ~GameRunningEvent() {};

		CScene* pScene = nullptr;
	};

	class GameNewLevelEvent : public Event<eGameStateEvents>
	{
	public:
		GameNewLevelEvent() :
			Event<eGameStateEvents>(eGameStateEvents::GAME_NEWLEVEL, "GameLevelUp") {};
		virtual ~GameNewLevelEvent() {};

		CScene* pScene = nullptr;
	};

	class GameOverEvent : public Event<eGameStateEvents>
	{
	public:
		GameOverEvent() :
			Event<eGameStateEvents>(eGameStateEvents::GAME_OVER, "GameOver") {};
		virtual ~GameOverEvent() {};

		CScene* pScene = nullptr;
	};
}
