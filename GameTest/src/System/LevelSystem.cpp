#include "stdafx.h"
#include "LevelSystem.h"
#include "src/Events/EventBusLocator.hpp"
#include "src/ECS/SComponents.h"
#include "src/Utilities/ComponentUtils.h"
#include "src/Utilities/GamplayUtils.h"

const float POSX = 500.0f;
const float POSY = 500.0f;
std::string EVENTTEXT = " EVENTS: ";
const float COLOR[3] = { 1.0f, 1.0f, 1.0f };


std::string Engine::LevelSystem::SystemName()
{
	return std::string();
}

void Engine::LevelSystem::Init()
{

	iEventBus<eGameStateEvents, GameStartedEvent>* pGameStarted = EventBusLocator<eGameStateEvents, GameStartedEvent>::Get();
	iEventBus<eGameStateEvents, GameRunningEvent>* pGameRuning = EventBusLocator<eGameStateEvents, GameRunningEvent>::Get();
	iEventBus<eGameStateEvents, GameNewLevelEvent>* pLeveUpBus = EventBusLocator<eGameStateEvents, GameNewLevelEvent>::Get();
	iEventBus<eGameStateEvents, GameOverEvent>* pEventBus = EventBusLocator<eGameStateEvents, GameOverEvent>::Get();

	pGameStarted->Subscribe(eGameStateEvents::GAME_STARTED, OnStart);
	pGameRuning->Subscribe(eGameStateEvents::GAME_RUNNING, OnRunning);
	pLeveUpBus->Subscribe(eGameStateEvents::GAME_NEWLEVEL, OnNewLevel);
	pEventBus->Subscribe(eGameStateEvents::GAME_OVER, OnGameOver);
}

void Engine::LevelSystem::Start(CScene* pScene)
{

	

}

void Engine::LevelSystem::Update(CScene* pScene, float deltaTime)
{
	GameStateComponent* pState = ComponentUtils::GetGameState();

	
	if (App::IsKeyPressed(eKeycodes::Z))
	{
		pState->currState = eGameStates::STARTED;
	}
	if (App::IsKeyPressed(eKeycodes::X))
	{

		
		pState->currState = eGameStates::RUNNING;

	}
	if (App::IsKeyPressed(eKeycodes::C))
	{
		pState->currState = eGameStates::NEWLEVEL;

	}
	if (App::IsKeyPressed(eKeycodes::V))
	{
		pState->currState = eGameStates::GAMEOVER;

	}
	

}

void Engine::LevelSystem::Render(CScene* pScene)
{
	App::Print(POSX, POSY, EVENTTEXT.c_str(), COLOR[0], COLOR[1], COLOR[2]);
}

void Engine::LevelSystem::End(CScene* pScene)
{
}

void Engine::LevelSystem::Cleanup()
{
	iEventBus<eGameStateEvents, GameStartedEvent>* pGameStarted = EventBusLocator<eGameStateEvents, GameStartedEvent>::Get();
	iEventBus<eGameStateEvents, GameRunningEvent>* pGameRuning = EventBusLocator<eGameStateEvents, GameRunningEvent>::Get();
	iEventBus<eGameStateEvents, GameNewLevelEvent>* pLeveUpBus = EventBusLocator<eGameStateEvents, GameNewLevelEvent>::Get();
	iEventBus<eGameStateEvents, GameOverEvent>* pEventBus = EventBusLocator<eGameStateEvents, GameOverEvent>::Get();

	pGameStarted->Unsubscribe(eGameStateEvents::GAME_STARTED, OnStart);
	pGameRuning->Unsubscribe(eGameStateEvents::GAME_RUNNING, OnRunning);
	pLeveUpBus->Unsubscribe(eGameStateEvents::GAME_NEWLEVEL, OnNewLevel);
	pEventBus->Unsubscribe(eGameStateEvents::GAME_OVER, OnGameOver);
}

void Engine::LevelSystem::OnStart(const GameStartedEvent& event)
{
	
	EVENTTEXT = "EVENT STARTED !";
}

void Engine::LevelSystem::OnRunning(const GameRunningEvent& event)
{
	event.pScene->DestroyAllEntities();

	EVENTTEXT = "EVENT RUNNING !";
	SystemFactory* systemFactory = ComponentUtils::GetFactory();

	GamplayUtils::CreateBackground(event.pScene, Vector2(510, 385));
	GamplayUtils::CreatePlayer(event.pScene, Vector2(400.0f, 400.0f));
	GamplayUtils::CreateCollidable(event.pScene, Vector2(200.0f, 200.0f));
	GamplayUtils::CreateCollidable(event.pScene, Vector2(600.0f, 200.0f));
	GamplayUtils::CreateHole(event.pScene, Vector2(800.0f, 600.0f));
	GamplayUtils::CreateHole(event.pScene, Vector2(800.0f, 200.0f));




	systemFactory->Start(event.pScene);


	
	


}

void Engine::LevelSystem::OnNewLevel(const GameNewLevelEvent& event)
{
	event.pScene->DestroyAllEntities();

	EVENTTEXT = "EVENT NEW LEVEL !";
	SystemFactory* systemFactory = ComponentUtils::GetFactory();

	GamplayUtils::CreateBackground(event.pScene, Vector2(510, 385));
	GamplayUtils::CreatePlayer(event.pScene, Vector2(400.0f, 400.0f));
	GamplayUtils::CreateCollidable(event.pScene, Vector2(200.0f, 200.0f));
	GamplayUtils::CreateCollidable(event.pScene, Vector2(600.0f, 200.0f));
	GamplayUtils::CreateHole(event.pScene, Vector2(800.0f, 600.0f));
	GamplayUtils::CreateHole(event.pScene, Vector2(800.0f, 200.0f));




	systemFactory->Start(event.pScene);


	


}

void Engine::LevelSystem::OnGameOver(const GameOverEvent& event)
{
	EVENTTEXT = "EVENT GAMEOVER !";

	event.pScene->DestroyAllEntities();

}
