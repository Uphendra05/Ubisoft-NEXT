#pragma once

#include "Event.hpp"

#include "src/ECS/CScene.h"

namespace Engine
{
	enum eGameStateEvents
	{
		GAME_STARTED,
		GAME_RUNNING,
		GAME_LEVELUP,
		GAME_OVER
	};

	class GameStartedEvent : public Event<eGameStateEvents>
	{
	public:
		GameStartedEvent() :
			Event<eGameStateEvents>(eGameStateEvents::GAME_STARTED, "GameStarted") {};
		virtual ~GameStartedEvent() {};

		CScene* pScene;
	};

	class GameRunningEvent : public Event<eGameStateEvents>
	{
	public:
		GameRunningEvent() :
			Event<eGameStateEvents>(eGameStateEvents::GAME_RUNNING, "GameRunning") {};
		virtual ~GameRunningEvent() {};

		CScene* pScene;
	};

	class GameLevelUpEvent : public Event<eGameStateEvents>
	{
	public:
		GameLevelUpEvent() :
			Event<eGameStateEvents>(eGameStateEvents::GAME_LEVELUP, "GameLevelUp") {};
		virtual ~GameLevelUpEvent() {};

		CScene* pScene;
	};

	class GameOverEvent : public Event<eGameStateEvents>
	{
	public:
		GameOverEvent() :
			Event<eGameStateEvents>(eGameStateEvents::GAME_OVER, "GameOver") {};
		virtual ~GameOverEvent() {};

		CScene* pScene;
	};
}
