#include "stdafx.h"
#include "LevelOne.h"
#include "src/Utilities/ComponentUtils.h"
#include "src/Utilities/PlayerUtilities.h"
#include "src/Events/EventBus.hpp"
#include "src/Events/EventBusLocator.hpp"

size_t result = 0;
std::string winLevel = " ";


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
    mMaxStrokes = 6;
    timer = 115;
    result = 0;
    winLevel = " ";
}

void Engine::LevelOne::Update(CScene* pScene, float deltaTime)
{
    deltaTime = deltaTime / 1000.0f;
    GameStateComponent* pState = ComponentUtils::GetGameState();


    if (pState->currState == eGameStates::RUNNING )
    {

       
       
        MovementComponent* pMove = pScene->GetComponent<MovementComponent>(PlayerUtilities::GetPlayerID(pScene));
        

        ScoreComponent* pScore = pScene->GetComponent<ScoreComponent>(PlayerUtilities::GetPlayerID(pScene));

        mStrokes = pScore->strokes;


        if (pScore->isGoal)
        {
            if (mStrokes == 1)
            {
                mGameStreaks = eGameStreaks::HOLEINONE;
                winLevel = "HOLE IN ONE";
            }
            else if(mStrokes >= 2 && mStrokes <= 4)
            {
                mGameStreaks = eGameStreaks::TWOTOFOUR;
                winLevel = "MID";

            }
            else
            {
                mGameStreaks = eGameStreaks::FIVETOSEVEN;
                winLevel = "NOOB";

            }

            result = PointStreaks(mStrokes, mMultiplier);

           
        }



        if (mStrokes >= mMaxStrokes && pMove->velocity == Vector2(0,0) && !pScore->isGoal)
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

      

        App::Print(10,  700,  objective.c_str() , 1, 1, 1);
        App::Print(200, 700, multiplier.c_str(), 1, 1, 1);
        App::Print(400, 700, strokes.c_str(), 1, 1, 1);
        App::Print(600, 700, maxStrokes.c_str(), 1, 1, 1);
        App::Print(800, 700, finalResult.c_str(), 1, 1, 1);
        App::Print(800, 200, winLevel.c_str(), 1, 1, 1);




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

size_t Engine::LevelOne::CalculateResult(size_t strokes, size_t points, size_t multiplier)
{
   
    size_t result  = points / strokes;
    result *= multiplier;
    return result;

}

size_t Engine::LevelOne::PointStreaks(size_t strokes, size_t multiplier)
{
    size_t _points = 0;


    switch (mGameStreaks)
    {
    case HOLEINONE:
        _points = 300;
        return CalculateResult(strokes, _points, multiplier);

        break;
    case TWOTOFOUR:
        _points = 100;
        return CalculateResult(strokes, _points, multiplier);

        break;
    case FIVETOSEVEN:
        _points = 50;

        return CalculateResult(strokes, _points, multiplier);

        break;
    default:
        return size_t();
        break;

    }




    
}

void Engine::LevelOne::OnCollision(const CollisionEnterEvent& event)
{

    CScene* pScene = event.collisionData.pScene;
    Entity entityActive = event.collisionData.entityA;
    Entity entityPassive = event.collisionData.entityB;

    Tag* passiveEntityTag = pScene->GetComponent<Tag>(entityPassive);
    ScoreComponent* pPlayer = pScene->GetComponent<ScoreComponent>(entityActive);

    if (passiveEntityTag->entityName == "Goal")
    {

        pPlayer->isGoal = true;

    }

    if (passiveEntityTag->entityName == "Red")
    {

        winLevel = "Red Ball Hit";
    }

    if (passiveEntityTag->entityName == "Blue")
    {

        winLevel = "Blue Ball Hit";

    }

    



}
