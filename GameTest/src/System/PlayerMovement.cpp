#include "stdafx.h"
#include "PlayerMovement.h"
#include "src/ECS/SComponentIterator.h"

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
        pMovement->drag = 5;
        pMovement->maxSpeed = 1000;
        pMovement->maxAcceleration = 1000;
    }

}

void Engine::PlayerMovement::Update(CScene* pScene, float deltaTime)
{

    for (Entity entityId : SComponentIterator<Transform, MovementComponent>(*pScene))
    {
        Transform* pTransform = pScene->GetComponent<Transform>(entityId);
        MovementComponent* pMovement = pScene->GetComponent<MovementComponent>(entityId);

        if (!pMovement->isStatic)
        {
            bool moving = false;


            if (App::IsKeyPressed(87))
            {
                MoveUpDown(pTransform, pMovement, -1);
                moving = true;

            }
            if (App::IsKeyPressed(83))
            {
                MoveUpDown(pTransform, pMovement, 1);
                moving = true;

            }
            if (App::IsKeyPressed(65))
            {
                MoveLeftRight(pTransform, pMovement, -1);
                moving = true;

            }
            if (App::IsKeyPressed(68))
            {
                MoveLeftRight(pTransform, pMovement, 1);
                moving = true;
            }

            if (!moving)
            {

                pMovement->acceleration = Vector2(0.0f, 0.0f);

            }

            //MakeBorders(pTransform->position.x, pTransform->position.y);

        }
        

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
