#include "stdafx.h"
#include "LevelOne.h"
#include "src/Utilities/ComponentUtils.h"
#include "src/Utilities/PlayerUtilities.h"
#include "src/Utilities/GraphicUtils.h"
#include "src/Events/EventBus.hpp"
#include "src/Events/EventBusLocator.hpp"
#include "src/Utilities/MathUtils.hpp"

size_t result = 0;
std::string winLevel = " ";

namespace Engine
{


    std::string Engine::LevelOne::SystemName()
    {
        return std::string();
    }

    void Engine::LevelOne::Init()
    {
    }

    void Engine::LevelOne::Start(CScene* pScene)
    {

        iEventBus<eCollisionEvents, CollisionEnterEvent>* pEventBus = EventBusLocator<eCollisionEvents, CollisionEnterEvent>::Get();
        pEventBus->Subscribe(eCollisionEvents::ONCOLLISION_ENTER, OnCollision);

        mObjectivePoints = 3000;
        mMultiplier = 15;
        mStrokes = 0;
        mMaxStrokes = 10;
        timer = 3.0f;
        result = 0;
        winLevel = " ";
        //MathUtils::Clamp(mStrokes, (size_t)0, mMaxStrokes);

    }

    void Engine::LevelOne::Update(CScene* pScene, float deltaTime)
    {
        deltaTime = deltaTime / 1000.0f;
        GameStateComponent* pState = ComponentUtils::GetGameState();


        if (pState->currState == eGameStates::RUNNING)
        {

            MovementComponent* pMove = pScene->GetComponent<MovementComponent>(PlayerUtilities::GetPlayerID(pScene));
            ScoreComponent* pScore = pScene->GetComponent<ScoreComponent>(PlayerUtilities::GetPlayerID(pScene));

            mStrokes = pScore->strokes;
            mMultiplier = pScore->multiplier;
            mMaxStrokes = pScore->maxStrokes;

            if (mStrokes == 1 || mStrokes == 0)
            {
                mGameStreaks = eGameStreaks::HOLEINONE;
                winLevel = "HOLE POINT: 500";
            }
            else if (mStrokes >= 2 && mStrokes <= 4)
            {
                mGameStreaks = eGameStreaks::TWOTOFOUR;
                winLevel = "HOLE POINT: 300";

            }
            else
            {
                mGameStreaks = eGameStreaks::FIVETOSEVEN;
                winLevel = "HOLE POINT: 100";

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

                result = PlayerUtilities::PointStreaks(mStrokes, mMultiplier, mGameStreaks);

                if (result >= mObjectivePoints)
                {
                    if (timer <= 0)
                    {
                        pState->currState = eGameStates::NEWLEVEL;
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

    void Engine::LevelOne::Render(CScene* pScene)
    {
        std::string objective = "OBJECTIVE : " + std::to_string(mObjectivePoints);
        std::string multiplier = "MULTIPLIER : " + std::to_string(mMultiplier);
        std::string strokes = "STROKES : " + std::to_string(mStrokes);
        std::string maxStrokes = "MAX STROKES : " + std::to_string(mMaxStrokes);
        std::string finalResult = "RESULT : " + std::to_string(result);

        GameStateComponent* pState = ComponentUtils::GetGameState();
        if (pState->currState == eGameStates::RUNNING)
        {

            App::Print(50, 700, objective.c_str(),   0, 0, 0);
            App::Print(250, 700, multiplier.c_str(), 0, 0, 0);
            App::Print(450, 700, strokes.c_str(),    0, 0, 0);
            App::Print(650, 700, maxStrokes.c_str(), 0, 0, 0);
            App::Print(850, 700, finalResult.c_str(),0, 0, 0);
            App::Print(850, 200, winLevel.c_str(),   0, 0, 0);

        }
    }

    void Engine::LevelOne::End(CScene* pScene)
    {
        GameStateComponent* pState = ComponentUtils::GetGameState();


        if (pState->currState == eGameStates::RUNNING)
        {

            iEventBus<eCollisionEvents, CollisionEnterEvent>* pEventBus = EventBusLocator<eCollisionEvents, CollisionEnterEvent>::Get();
            pEventBus->Unsubscribe(eCollisionEvents::ONCOLLISION_ENTER, OnCollision);
        }
    }

    void Engine::LevelOne::Cleanup()
    {


    }


    void Engine::LevelOne::OnCollision(const CollisionEnterEvent& event)
    {
        GameStateComponent* pState = ComponentUtils::GetGameState();
        if (pState->currState == eGameStates::RUNNING)
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
//TODO : Change Timer 
