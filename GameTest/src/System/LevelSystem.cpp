#include "stdafx.h"
#include "LevelSystem.h"
#include "src/Events/EventBusLocator.hpp"
#include "src/ECS/SComponents.h"
#include "src/Utilities/ComponentUtils.h"
#include "src/Utilities/GamplayUtils.h"
#include "src/Utilities/GraphicUtils.h"
#include "src/Gamplay/ObjectPool.h"
#include "src/Gamplay/UITexts.hpp"



namespace Engine
{


// TODO : should refactor this code and should find a way to remove gameplay systems and add them again.

std::string Engine::LevelSystem::SystemName()
{
	return std::string();
}

void Engine::LevelSystem::Init()
{

	iEventBus<eGameStateEvents, GameStartedEvent>* pGameStarted = EventBusLocator<eGameStateEvents, GameStartedEvent>::Get();
	iEventBus<eGameStateEvents, GameControlsEvent>* pGameControls = EventBusLocator<eGameStateEvents, GameControlsEvent>::Get();
	iEventBus<eGameStateEvents, GameRunningEvent>* pGameRuning = EventBusLocator<eGameStateEvents, GameRunningEvent>::Get();
	iEventBus<eGameStateEvents, GameNewLevelEvent>* pLeveUpBus = EventBusLocator<eGameStateEvents, GameNewLevelEvent>::Get();
	iEventBus<eGameStateEvents, GameOverEvent>* pEventBus = EventBusLocator<eGameStateEvents, GameOverEvent>::Get();

	pGameStarted->Subscribe(eGameStateEvents::GAME_STARTED, OnStart);
	pGameControls->Subscribe(eGameStateEvents::GAME_CONTROLS, OnControls);
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

	if (pState->currState == eGameStates::STARTED || pState->currState == eGameStates::GAMEOVER)
	{
		if (App::IsKeyPressed(eKeycodes::E))
		{
			//GameStateComponent* pState = ComponentUtils::GetGameState();
			pState->currState = eGameStates::CONTROLS;
			App::PlaySoundW(".\\Assets\\Sounds\\Menu.wav", false);

			
			

		}
		
	}

	if (pState->currState == eGameStates::CONTROLS && App::IsKeyPressed(eKeycodes::F))
	{

		//GameStateComponent* pState = ComponentUtils::GetGameState();
		pState->currState = eGameStates::RUNNING;
		App::PlaySoundW(".\\Assets\\Sounds\\Menu.wav", false);


	}
	
	
	

}

void Engine::LevelSystem::Render(CScene* pScene)
{
	GameStateComponent* pState = ComponentUtils::GetGameState();

	if (pState->currState == eGameStates::STARTED )
	{
		App::Print(POSITIONX, POSITIONY - 50, TITLE.c_str(), COLOR[0], COLOR[1], COLOR[2]);

		

	}
	if (pState->currState == eGameStates::CONTROLS)
	{
		App::Print(POSITIONX, POSITIONY - 50, TITLE.c_str(), COLOR[0], COLOR[1], COLOR[2]);

		App::Print(REDBALLPOSX, REDBALLPOSY, "RED BALL REDUCES YOUR MAX STROKES", REDBALLCOLOR[0], REDBALLCOLOR[1], REDBALLCOLOR[2]);
		App::Print(REDBALLPOSX + 20, REDBALLPOSY - 30, "BUT BOOSTS YOUR MULTIPLIER", REDBALLCOLOR[0], REDBALLCOLOR[1], REDBALLCOLOR[2]);
		App::Print(REDBALLPOSX, REDBALLPOSY - 60, "ALSO GREATLY INCREASES BOUNCINESS", REDBALLCOLOR[0], REDBALLCOLOR[1], REDBALLCOLOR[2]);


		App::Print(BLUEBALLPOSX, BLUEBALLPOSY, "BLUE BALL INCREASES YOUR MAX STROKES", BLUEBALLCOLOR[0], BLUEBALLCOLOR[1], BLUEBALLCOLOR[2]);
		App::Print(BLUEBALLPOSX + 20, BLUEBALLPOSY - 30, "BUT REDUCES YOUR MULTIPLIER", BLUEBALLCOLOR[0], BLUEBALLCOLOR[1], BLUEBALLCOLOR[2]);
		App::Print(BLUEBALLPOSX, BLUEBALLPOSY - 60, "ALSO GREATLY DECREASES BOUNCINESS", BLUEBALLCOLOR[0], BLUEBALLCOLOR[1], BLUEBALLCOLOR[2]);
		
		App::Print(INSTRUCTIONSPOSX, INSTRUCTIONSPOSY - 50, "PRESS AND HOLD SPACE TO CHARGE BALL AND RELEASE TO SHOOT", INSTRUCTIONSCOLOR[0], INSTRUCTIONSCOLOR[1], INSTRUCTIONSCOLOR[2]);
		App::Print(INSTRUCTIONSPOSX + 40, INSTRUCTIONSPOSY - 100, "USE YOUR MOUSE TO CONTROL DIRECTION OF YOUR BALL", INSTRUCTIONSCOLOR[0], INSTRUCTIONSCOLOR[1], INSTRUCTIONSCOLOR[2]);
		App::Print(INSTRUCTIONSPOSX + 100, INSTRUCTIONSPOSY - 150, "GET THE OBJECTIVE POINT TO WIN LEVEL", INSTRUCTIONSCOLOR[0], INSTRUCTIONSCOLOR[1], INSTRUCTIONSCOLOR[2]);
		App::Print(INSTRUCTIONSPOSX + 100, INSTRUCTIONSPOSY - 200, "YOUR MULTIPLIER BOOSTS YOUR POINTS", INSTRUCTIONSCOLOR[0], INSTRUCTIONSCOLOR[1], INSTRUCTIONSCOLOR[2]);
		App::Print(INSTRUCTIONSPOSX + 120, INSTRUCTIONSPOSY - 250, "HIGHER THE STROKES LESSER THE POINTS", INSTRUCTIONSCOLOR[0], INSTRUCTIONSCOLOR[1], INSTRUCTIONSCOLOR[2]);
		App::Print(INSTRUCTIONSPOSX + 40, INSTRUCTIONSPOSY - 300, "EACH TIME YOU LOAD A LEVEL YOU GET A RANDOM LEVEL MODIFIER", INSTRUCTIONSCOLOR[0], INSTRUCTIONSCOLOR[1], INSTRUCTIONSCOLOR[2]);
		App::Print(INSTRUCTIONSPOSX + 40, INSTRUCTIONSPOSY - 350, "CHOOSE YOUR BALL COLORS WISELY TO FINISH THE LEVEL", INSTRUCTIONSCOLOR[0], INSTRUCTIONSCOLOR[1], INSTRUCTIONSCOLOR[2]);



	}
	if (pState->currState == eGameStates::GAMEOVER)
	{
		App::Print(POSITIONX, POSITIONY, TITLE.c_str(), COLOR[0], COLOR[1], COLOR[2]);
	}
	



}

void Engine::LevelSystem::End(CScene* pScene)
{

}

void Engine::LevelSystem::Cleanup()
{
	iEventBus<eGameStateEvents, GameStartedEvent>* pGameStarted = EventBusLocator<eGameStateEvents, GameStartedEvent>::Get();
	iEventBus<eGameStateEvents, GameControlsEvent>* pGameControls = EventBusLocator<eGameStateEvents, GameControlsEvent>::Get();
	iEventBus<eGameStateEvents, GameRunningEvent>* pGameRuning = EventBusLocator<eGameStateEvents, GameRunningEvent>::Get();
	iEventBus<eGameStateEvents, GameNewLevelEvent>* pLeveUpBus = EventBusLocator<eGameStateEvents, GameNewLevelEvent>::Get();
	iEventBus<eGameStateEvents, GameOverEvent>* pEventBus = EventBusLocator<eGameStateEvents, GameOverEvent>::Get();

	pGameStarted->Unsubscribe(eGameStateEvents::GAME_STARTED, OnStart);
	pGameControls->Unsubscribe(eGameStateEvents::GAME_STARTED, OnControls);
	pGameRuning->Unsubscribe(eGameStateEvents::GAME_RUNNING, OnRunning);
	pLeveUpBus->Unsubscribe(eGameStateEvents::GAME_NEWLEVEL, OnNewLevel);
	pEventBus->Unsubscribe(eGameStateEvents::GAME_OVER, OnGameOver);



	ComponentUtils::Clear();
}

void Engine::LevelSystem::OnStart(const GameStartedEvent& event)
{
	GamplayUtils::CreateBackground(event.pScene, Vector2(510, 385));
	GamplayUtils::CreateTitle(event.pScene, Vector2(510, 385));
	
	TITLE = "PRESS E TO START";

}

void Engine::LevelSystem::OnControls(const GameControlsEvent& event)
{
	event.pScene->DestroyAllEntities();
	GamplayUtils::CreateBackground(event.pScene, Vector2(510, 385));

	GamplayUtils::CreateBlueUi(event.pScene, Vector2(810, 650));
	GamplayUtils::CreateRedUi(event.pScene, Vector2(210,  650));
	TITLE = "PRESS F TO CONTINUE";
}

void Engine::LevelSystem::OnRunning(const GameRunningEvent& event)
{
	
	

	LevelOne(event);
	
	


}

void Engine::LevelSystem::OnNewLevel(const GameNewLevelEvent& event)
{
	

	LevelTwo(event);
	


}

void Engine::LevelSystem::OnGameOver(const GameOverEvent& event)
{

	event.pScene->DestroyAllEntities();
	GamplayUtils::CreateBackground(event.pScene, Vector2(510, 385));
	GamplayUtils::CreateGameOver(event.pScene, Vector2(510, 385));
	TITLE = "PRESS E TO RESTART GAME";
	

}

void Engine::LevelSystem::LevelOne(const GameRunningEvent& event)
{

	event.pScene->DestroyAllEntities();

	SystemFactory* systemFactory = ComponentUtils::GetSystemFactory();


	GamplayUtils::CreateBackground(event.pScene, Vector2(510, 385));
	GamplayUtils::CreateGoal(event.pScene, Vector2(100.0f, 100.0f));
	GamplayUtils::CreatePlayer(event.pScene, Vector2(100.0f, 400.0f));
	GamplayUtils::CreateRed(event.pScene, Vector2(50.0f, 600.0f));
	GamplayUtils::CreateBlue(event.pScene, Vector2(150.0f, 600.0f));

	
	GamplayUtils::CreateCollidable2(event.pScene, Vector2(950.0f, 100.0f));
	GamplayUtils::CreateCollidable2(event.pScene, Vector2(300.0f, 400.0f));

	GamplayUtils::CreateCollidable3(event.pScene, Vector2(400.0f, 600.0f));

	

	GamplayUtils::CreateWall(event.pScene, Vector2(675.0f, 700.0f));
	GamplayUtils::CreateWall2(event.pScene, Vector2(375.0f, 200.0f));
	GamplayUtils::CreateWall2(event.pScene, Vector2(1275.0f, 300.0f));

	GamplayUtils::CreateFogOfWar(event.pScene, Vector2(0, 0));




	systemFactory->Start(event.pScene);



	



}

void Engine::LevelSystem::LevelTwo(const GameNewLevelEvent& event)
{
	event.pScene->DestroyAllEntities();

	SystemFactory* systemFactory = ComponentUtils::GetSystemFactory();

	GamplayUtils::CreateBackground(event.pScene, Vector2(510, 385));
	GamplayUtils::CreateGoal(event.pScene, Vector2(700.0f, 100.0f));
	GamplayUtils::CreatePlayer(event.pScene, Vector2(100.0f, 100.0f));
	GamplayUtils::CreateRed(event.pScene, Vector2(50.0f, 200.0f));
	GamplayUtils::CreateBlue(event.pScene, Vector2(150.0f, 200.0f));

	GamplayUtils::CreateCollidable(event.pScene, Vector2(300.0f, 400.0f));
	GamplayUtils::CreateCollidable(event.pScene, Vector2(700.0f, 600.0f));
	GamplayUtils::CreateCollidable(event.pScene, Vector2(800.0f, 200.0f));


	GamplayUtils::CreateCollidable(event.pScene, Vector2(450.0f, 345.0f));

	GamplayUtils::CreateCollidable2(event.pScene, Vector2(800.0f, 400.0f));
	GamplayUtils::CreateCollidable2(event.pScene, Vector2(600.0f, 100.0f));

	GamplayUtils::CreateCollidable3(event.pScene, Vector2(400.0f, 600.0f));

	GamplayUtils::CreateWall(event.pScene, Vector2(250.0f, 705.0f));
	GamplayUtils::CreateWall(event.pScene, Vector2(250.0f, 165.0f));

	GamplayUtils::CreateFogOfWar(event.pScene, Vector2(0, 0));


	//GamplayUtils::CreateHole(event.pScene, Vector2(800.0f, 600.0f));
	//GamplayUtils::CreateHole(event.pScene, Vector2(800.0f, 200.0f));




	systemFactory->Start(event.pScene);
	
}
}
