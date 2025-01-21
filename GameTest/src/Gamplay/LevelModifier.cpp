#include "stdafx.h"
#include "LevelModifier.h"
#include "src/ECS/SComponents.h"
#include "src/Utilities/ComponentUtils.h"
#include "src/Utilities/PlayerUtilities.h"
#include <random>


namespace Engine
{


//LEVEL MODIFIER
const float MODIFIERPOSX = 400.0f;
const float MODIFIERPOSY = 30.0f;
extern std::string MODIFIER = " ";
const float MODIFIERCOLOR[3] = { 0.0f, 0.0f, 0.0f };

std::string Engine::LevelModifier::SystemName()
{
    return std::string();
}

void Engine::LevelModifier::Init()
{
}

void Engine::LevelModifier::Start(CScene* pScene)
{
	//Rigidbody* pPlayerRb = pScene->GetComponent<Rigidbody>(PlayerUtilities::GetPlayerID(pScene));
	//SpriteRenderer* pFogOfWar = pScene->GetComponent<SpriteRenderer>(PlayerUtilities::GetFogOfWarID(pScene));
	//MovementComponent* pPlayerMove = pScene->GetComponent<MovementComponent>(PlayerUtilities::GetPlayerID(pScene));

	
		//pPlayerRb->useGravity = false;	
		//pPlayerMove->isWobble = false;	
		//pPlayerMove->drag = 2.5f;	
		//pFogOfWar->isVisible = false;

	isModified = false;
	
}

void Engine::LevelModifier::Update(CScene* pScene, float deltaTime)
{

	GameStateComponent* pState = ComponentUtils::GetGameState();

	if (pState->currState == eGameStates::RUNNING && !isModified)
	{
		
		static std::random_device rd;
		static std::mt19937 gen(rd());
		std::uniform_int_distribution<size_t> dist(0, modifiers.size() - 1);

		mLevelModifier = modifiers[dist(gen)];
		DecideLevelModifier(pScene, deltaTime);
		isModified = true;
	}

	if (pState->currState == eGameStates::NEWLEVEL && !isModified)
	{

		static std::random_device rd;
		static std::mt19937 gen(rd());
		std::uniform_int_distribution<size_t> dist(0, modifiers.size() - 1);

		mLevelModifier = modifiers[dist(gen)];
		DecideLevelModifier(pScene, deltaTime);
		isModified = true;
	}

}

void Engine::LevelModifier::Render(CScene* pScene)
{
	GameStateComponent* pState = ComponentUtils::GetGameState();

	if (pState->currState == eGameStates::RUNNING && isModified)
	{
		App::Print(MODIFIERPOSX, MODIFIERPOSY, MODIFIER.c_str(), MODIFIERCOLOR[0], MODIFIERCOLOR[1], MODIFIERCOLOR[2]);
	}
	if (pState->currState == eGameStates::NEWLEVEL && isModified)
	{
		App::Print(MODIFIERPOSX, MODIFIERPOSY, MODIFIER.c_str(), MODIFIERCOLOR[0], MODIFIERCOLOR[1], MODIFIERCOLOR[2]);
	}
}

void Engine::LevelModifier::End(CScene* pScene)
{
}

void Engine::LevelModifier::Cleanup()
{
}

void Engine::LevelModifier::DecideLevelModifier(CScene* pScene, float deltaTime)
{
	GameStateComponent* pState = ComponentUtils::GetGameState();

	
	if (pState->currState == eGameStates::RUNNING || pState->currState == eGameStates::NEWLEVEL)
	{
		Rigidbody* pPlayerRb = pScene->GetComponent<Rigidbody>(PlayerUtilities::GetPlayerID(pScene));
		SpriteRenderer* pFogOfWar = pScene->GetComponent<SpriteRenderer>(PlayerUtilities::GetFogOfWarID(pScene));
		MovementComponent* pPlayerMove = pScene->GetComponent<MovementComponent>(PlayerUtilities::GetPlayerID(pScene));

		switch (mLevelModifier)
		{
	
		case UNPREDTICTABLEMOVE:
			MODIFIER = "LEVEL MODIFIER: UNPREDTICTABLE MOVEMENT";
			pPlayerMove->isWobble = true;
			break;
		case RIGIDMOVEMENT:
			MODIFIER = "LEVEL MODIFIER: RIGID MOVEMENT";

			pPlayerMove->drag = 5.2f;
			break;
		case FOGOFWAR:
			MODIFIER = "LEVEL MODIFIER: FOG OF WAR";

			pFogOfWar->isVisible = true;
			break;
		default:
			break;
		}
	}


}


}