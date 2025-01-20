#include "stdafx.h"
#include "PlayerMovement.h"
#include "src/ECS/SComponentIterator.h"
#include "src/Utilities/PlayerUtilities.h"

const float CHARGEPOWERX = 600.0f;
const float CHARGEPOWERY = 600.0f;
std::string CHARGEPOWERTEXT = " POWER ";
const float COLOR[3] = { 1.0f, 1.0f, 1.0f };


std::string Engine::PlayerMovement::SystemName()
{
    return std::string();
}

void Engine::PlayerMovement::Init()
{
}

void Engine::PlayerMovement::Start(CScene* pScene)
{

    for (Entity entityId : SComponentIterator<MovementComponent>(*pScene))
    {
       
        MovementComponent* pMovement = pScene->GetComponent<MovementComponent>(entityId);

        pMovement->acceleration = Vector2(0.0f, 0.0f);
        pMovement->velocity = Vector2(0.0f, 0.0f);
        pMovement->drag = 2.5f;
        pMovement->maxSpeed = 2000;
        pMovement->maxAcceleration = 1000;

        pMovement->chargePower = 0.0f;  // Current shot power
        pMovement->maxPower = 2000.0f;   // Maximum shot power
        pMovement->chargeRate = 200.0f; // Rate of power increase per second


    }

}

void Engine::PlayerMovement::Update(CScene* pScene, float deltaTime)
{
    deltaTime = deltaTime / 100.0f;
    CHARGEPOWERTEXT = "POWER : " ;

    for (Entity entityId : SComponentIterator<Transform, MovementComponent, ScoreComponent, SpriteRenderer>(*pScene))
    {
        Transform* pTransform = pScene->GetComponent<Transform>(entityId);
        MovementComponent* pMovement = pScene->GetComponent<MovementComponent>(entityId);
        ScoreComponent* pScore = pScene->GetComponent<ScoreComponent>(entityId);
        SpriteRenderer* pSprite = pScene->GetComponent<SpriteRenderer>(entityId);

       
       
        if (!pMovement->isStatic && pScore->strokes < pScore->maxStrokes && pSprite->isVisible)
        {
            bool moving = false;

            // Golf shot mechanics
            if (App::IsKeyPressed(32)) // Start charging
            {
                pMovement->isCharging = true;
                pMovement->chargePower += pMovement->chargeRate * deltaTime;

                // Cap the charge power
                if (pMovement->chargePower > pMovement->maxPower)
                {
                    pMovement->chargePower = pMovement->maxPower;
                }
                moving = true;
            }
            else if (pMovement->isCharging && !App::IsKeyPressed(32)) // Release shot
            {
                pMovement->isCharging = false;

                Vector2 mousePos = Vector2() ;
                App::GetMousePos(mousePos.x, mousePos.y);
                Vector2 direction = mousePos - pTransform->position;
               
                pMovement->velocity = direction.normalized() * pMovement->chargePower ;

                // Reset charge power
                pMovement->chargePower = 0.0f;
                pScore->strokes +=1 ;
                moving = false;
            }

           

        }
        
        MakeBorders(pTransform->position.x, pTransform->position.y);

    }
}

void Engine::PlayerMovement::Render(CScene* pScene)
{

  

}

void Engine::PlayerMovement::End(CScene* pScene)
{
}

void Engine::PlayerMovement::Cleanup()
{
}

void Engine::PlayerMovement::MoveUpDown(Transform* pTransform, MovementComponent* pMovement, int direction)
{
    Vector2 upVector;
    upVector.normalized();
    pMovement->acceleration += (upVector.down() * (float)direction * 1000);



}

void Engine::PlayerMovement::MakeBorders(float& x, float& y)
{
    if (x > APP_VIRTUAL_WIDTH)
    {
        x = APP_VIRTUAL_WIDTH;
    }
    else if (x < 0.0f)
    {
        x = 0.0f;
    }

    if (y > APP_VIRTUAL_HEIGHT)
    {
        y = APP_VIRTUAL_HEIGHT;
    }
    else if (y < 0.0f)
    {
        y = 0.0f;
    }
}

void Engine::PlayerMovement::MoveLeftRight(Transform* pTransform, MovementComponent* pMovement, int direction)
{

    float forwardX = std::cos(pTransform->worldrotation);
    float forwardY = std::sin(pTransform->worldrotation);

    Vector2 forward = Vector2(forwardX, forwardY).normalized();

    pMovement->acceleration +=  (forward * (float)direction * 1000);

}
