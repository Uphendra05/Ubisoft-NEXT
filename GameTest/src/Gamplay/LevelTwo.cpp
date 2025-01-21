#include "stdafx.h"
#include "LevelTwo.h"
#include "src/Utilities/ComponentUtils.h"
#include "src/Utilities/PlayerUtilities.h"
#include "src/Utilities/GraphicUtils.h"
#include "src/Events/EventBus.hpp"
#include "src/Events/EventBusLocator.hpp"
#include "src/Utilities/MathUtils.hpp"



namespace Engine
{
    size_t result2 = 0;
    std::string winLevel2 = " ";

	std::string Engine::LevelTwo::SystemName()
	{
		return std::string();
	}

	void Engine::LevelTwo::Init()
	{
	}

	void Engine::LevelTwo::Start(CScene* pScene)
	{
		iEventBus<eCollisionEvents, CollisionEnterEvent>* pEventBus = EventBusLocator<eCollisionEvents, CollisionEnterEvent>::Get();
		pEventBus->Subscribe(eCollisionEvents::ONCOLLISION_ENTER, OnCollision);

		mObjectivePoints = 4000;
		mMultiplier = 25;
		mStrokes = 0;
		mMaxStrokes = 6;
		timer = 3.0f;
		result2 = 0;
		winLevel2 = " ";
	}

	void Engine::LevelTwo::Update(CScene* pScene, float deltaTime)
	{
        deltaTime = deltaTime / 1000.0f;
        GameStateComponent* pState = ComponentUtils::GetGameState();


        if (pState->currState == eGameStates::NEWLEVEL)
        {

            MovementComponent* pMove = pScene->GetComponent<MovementComponent>(PlayerUtilities::GetPlayerID(pScene));
            ScoreComponent* pScore = pScene->GetComponent<ScoreComponent>(PlayerUtilities::GetPlayerID(pScene));

            mStrokes = pScore->strokes;
            mMultiplier = pScore->multiplier;
            mMaxStrokes = pScore->maxStrokes;

            if (mStrokes == 1 || mStrokes == 0)
            {
                mGameStreaks = eGameStreaks::HOLEINONE;
                winLevel2 = "HOLE POINT: 500";
            }
            else if (mStrokes >= 2 && mStrokes <= 4)
            {
                mGameStreaks = eGameStreaks::TWOTOFOUR;
                winLevel2 = "HOLE POINT: 300";

            }
            else
            {
                mGameStreaks = eGameStreaks::FIVETOSEVEN;
                winLevel2 = "HOLE POINT: 100";

            }



            if (pScore->isGoal)
            {
                if (mStrokes == 1)
                {
                    mGameStreaks = eGameStreaks::HOLEINONE;
                }
                else if (mStrokes >= 2 && mStrokes <= 4)
                {
                    mGameStreaks = eGameStreaks::TWOTOFOUR;

                }
                else
                {
                    mGameStreaks = eGameStreaks::FIVETOSEVEN;

                }

                result2 = PlayerUtilities::PointStreaks(mStrokes, mMultiplier, mGameStreaks);

                if (result2 >= mObjectivePoints)
                {
                    if (timer <= 0)
                    {
                        pState->currState = eGameStates::GAMEOVER;
                    }
                    else
                    {
                        timer -= 1 * deltaTime;
                    }
                }
                else
                {
                    if (timer <= 0)
                    {
                        pState->currState = eGameStates::GAMEOVER;
                    }
                    else
                    {
                        timer -= 1 * deltaTime;
                    }
                }
            }


            if (mStrokes >= mMaxStrokes && pMove->velocity == Vector2(0, 0) && !pScore->isGoal)
            {


                if (timer <= 0)
                {
                    pState->currState = eGameStates::GAMEOVER;
                }
                else
                {
                    timer -= 1 * deltaTime;
                }


            }


        }

	}

	void Engine::LevelTwo::Render(CScene* pScene)
	{
        std::string objective = "OBJECTIVE : " + std::to_string(mObjectivePoints);
        std::string multiplier = "MULTIPLIER : " + std::to_string(mMultiplier);
        std::string strokes = "STROKES : " + std::to_string(mStrokes);
        std::string maxStrokes = "MAX STROKES : " + std::to_string(mMaxStrokes);
        std::string finalResult = "RESULT : " + std::to_string(result2);

        GameStateComponent* pState = ComponentUtils::GetGameState();


        if (pState->currState == eGameStates::NEWLEVEL)
        {

            App::Print(50, 700, objective.c_str(),   0, 0, 0);
            App::Print(250, 700, multiplier.c_str(), 0, 0, 0);
            App::Print(450, 700, strokes.c_str(),    0, 0, 0);
            App::Print(650, 700, maxStrokes.c_str(), 0, 0, 0);
            App::Print(850, 700, finalResult.c_str(),0, 0, 0);
            App::Print(850, 200, winLevel2.c_str(),  0, 0, 0);

        }
	}

	void Engine::LevelTwo::End(CScene* pScene)
	{
        GameStateComponent* pState = ComponentUtils::GetGameState();


        if (pState->currState == eGameStates::NEWLEVEL)
        {

            iEventBus<eCollisionEvents, CollisionEnterEvent>* pEventBus = EventBusLocator<eCollisionEvents, CollisionEnterEvent>::Get();
            pEventBus->Unsubscribe(eCollisionEvents::ONCOLLISION_ENTER, OnCollision);
        }
	}

	void Engine::LevelTwo::Cleanup()
	{

	}

	void LevelTwo::OnCollision(const CollisionEnterEvent& event)
	{
        GameStateComponent* pState = ComponentUtils::GetGameState();
        if (pState->currState == eGameStates::NEWLEVEL)
        {
            CScene* pScene = event.collisionData.pScene;
            Entity entityActive = event.collisionData.entityA;
            Entity entityPassive = event.collisionData.entityB;

            Tag* passiveEntityTag = pScene->GetComponent<Tag>(entityPassive);
            Transform* pTransform = pScene->GetComponent<Transform>(entityActive);
            ScoreComponent* pPlayer = pScene->GetComponent<ScoreComponent>(entityActive);
            SpriteRenderer* pSprite = pScene->GetComponent<SpriteRenderer>(entityActive);
            Rigidbody* pRb = pScene->GetComponent<Rigidbody>(entityActive);

            if (passiveEntityTag->entityName == "Goal")
            {

                pPlayer->isGoal = true;
                pSprite->isVisible = false;
                App::PlaySoundW(".\\Assets\\Sounds\\Pocket.wav", false);

            }
            if (passiveEntityTag->entityName == "Red")
            {

                pSprite->sprite = new CSimpleSprite(".\\Assets\\Red.png", 1, 1);
                pPlayer->maxStrokes = 7;
                pPlayer->multiplier = 100;
                pRb->bounciness = 2.7f;
                App::PlaySoundW(".\\Assets\\Sounds\\Power.wav", false);


            }
            if (passiveEntityTag->entityName == "Blue")
            {
                pSprite->sprite = new CSimpleSprite(".\\Assets\\Blue.png", 1, 1);
                pPlayer->maxStrokes = 13;
                pPlayer->multiplier = 50;
                pRb->bounciness = 0.8f;
                App::PlaySoundW(".\\Assets\\Sounds\\Power.wav", false);



            }
        }

	}

}
