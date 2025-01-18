#include "stdafx.h"
#include "ShuffleHoleSystem.h"
#include "src/ECS/SComponentIterator.h"
#include <random>
#include "App/app.h"

std::string Engine::ShuffleHoleSystem::SystemName()
{
    return std::string();
}

void Engine::ShuffleHoleSystem::Init()
{
}

void Engine::ShuffleHoleSystem::Start(CScene* pScene)
{

    for (Entity entity : SComponentIterator<ShuffleHoleComponent,Transform>(*pScene))
    {
        Transform* pTransform = pScene->GetComponent<Transform>(entity);
        ShuffleHoleComponent* pHole = pScene->GetComponent<ShuffleHoleComponent>(entity);

        pHole->position = pTransform->position;

        movableEntities.push_back(entity);
    }

    

}

void Engine::ShuffleHoleSystem::Update(CScene* pScene, float deltaTime)
{
    

        if (movableEntities.size() > 1)
        {
            ShufflePositions(pScene, movableEntities);

        }

}

void Engine::ShuffleHoleSystem::Render(CScene* pScene)
{
}

void Engine::ShuffleHoleSystem::End(CScene* pScene)
{
}

void Engine::ShuffleHoleSystem::Cleanup()
{
}

void Engine::ShuffleHoleSystem::ShufflePositions(CScene* pScene, std::vector<Entity>& entities)
{
    std::vector<Vector2> positions;
    for (Entity entity : entities)
    {
        Transform* transform = pScene->GetComponent<Transform>(entity);
        if (transform)
        {
            positions.push_back(transform->position);
        }
    }

    std::random_device rd;
    std::mt19937 g(rd());
    std::shuffle(positions.begin(), positions.end(), g);

    for (size_t i = 0; i < entities.size(); ++i)
    {
        Transform* transform = pScene->GetComponent<Transform>(entities[i]);
        ShuffleHoleComponent* pHole = pScene->GetComponent<ShuffleHoleComponent>(entities[i]);

        if (transform && pHole)
        {
            pHole->targetPosition = positions[i];
            pHole->isMoving = true;
        }
    }

}
