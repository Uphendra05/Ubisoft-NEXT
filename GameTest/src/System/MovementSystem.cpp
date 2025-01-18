#include "stdafx.h"
#include "MovementSystem.h"
#include "src/ECS/SComponentIterator.h"

std::string Engine::MovementSystem::SystemName()
{
    return std::string();
}

void Engine::MovementSystem::Init()
{
}

void Engine::MovementSystem::Start(CScene* pScene)
{
}

void Engine::MovementSystem::Update(CScene* pScene, float deltaTime)
{
    float minSpeed = 10.0f;
    deltaTime = deltaTime / 1000.0f;
    timer += deltaTime;

    // Update velocity and position
    for (Entity entityId : SComponentIterator<Transform, MovementComponent>(*pScene))
    {
        Transform* pTransform = pScene->GetComponent<Transform>(entityId);
        MovementComponent* pMovement = pScene->GetComponent<MovementComponent>(entityId);

        // Clip acceleration to max
        float currentAcceleration = pMovement->acceleration.magnitude();
        if (currentAcceleration > pMovement->maxAcceleration)
        {
            pMovement->acceleration = pMovement->acceleration.normalized() * pMovement->maxAcceleration;
        }

        Vector2 newVelocity = pMovement->velocity + (pMovement->acceleration * deltaTime);
        Vector2 dragForce = newVelocity * -(pMovement->drag * deltaTime);
        pMovement->velocity = newVelocity + dragForce;

        // Clip velocity between min and max
        float currentSpeed = pMovement->velocity.magnitude();
        if (currentSpeed > pMovement->maxSpeed)
        {
            pMovement->velocity = pMovement->velocity.normalized() * pMovement->maxSpeed;
        }
        else if (currentSpeed <= minSpeed)
        {
            pMovement->velocity = Vector2(0.0f, 0.0f);
        }

        pTransform->position += (pMovement->velocity * deltaTime);
    }
}

void Engine::MovementSystem::Render(CScene* pScene)
{

}

void Engine::MovementSystem::End(CScene* pScene)
{
}

void Engine::MovementSystem::Cleanup()
{
}
