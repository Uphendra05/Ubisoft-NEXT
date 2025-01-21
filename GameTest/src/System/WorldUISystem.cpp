#include "stdafx.h"
#include "WorldUISystem.h"
#include "src/ECS/SComponentIterator.h"
#include "src/ECS/SComponents.h"




std::string Engine::WorldUISystem::SystemName()
{
    return std::string();
}

void Engine::WorldUISystem::Init()
{
}

void Engine::WorldUISystem::Start(CScene* pScene)
{
}

void Engine::WorldUISystem::Update(CScene* pScene, float deltaTime)
{
}

void Engine::WorldUISystem::Render(CScene* pScene)
{
    for (Entity entityId : SComponentIterator<MovementComponent>(*pScene))
    {
        MovementComponent* pMovement = pScene->GetComponent<MovementComponent>(entityId);
        Transform* pTransform = pScene->GetComponent<Transform>(entityId);

        if (pMovement && pTransform)
        {
            // Debug power line visualization
            if (pMovement->isCharging)
            {
                Vector2 mousePos = Vector2();
                App::GetMousePos(mousePos.x, mousePos.y);
                Vector2 direction = mousePos - pTransform->position;
                Vector2 shotDirection = direction.normalized();

                if (pMovement->isWobble)
                {
                    float wobbleStrength = 0.3f; // Adjust wobble intensity
                    shotDirection.x += (static_cast<float>(std::rand()) / RAND_MAX - 0.5f) * wobbleStrength;
                    shotDirection.y += (static_cast<float>(std::rand()) / RAND_MAX - 0.5f) * wobbleStrength;
                    shotDirection = shotDirection.normalized();

                }


                // Calculate the start and end points of the debug line
                Vector2 startPoint = pTransform->position; // Start at the entity's position
                Vector2 endPoint = startPoint + shotDirection * (pMovement->chargePower * 0.1f);

                // Draw the debug line
                float color[3] = { 0.0f, 0.0f, 1.0f };
                App::DrawLine(startPoint.x, startPoint.y, endPoint.x, endPoint.y, color[0], color[1], color[2]);
            }
        }
    }

	
}

void Engine::WorldUISystem::End(CScene* pScene)
{
}

void Engine::WorldUISystem::Cleanup()
{
}
