#include "stdafx.h"
#include "DebugAABB.h"

#include "App/app.h"
#include "src/ECS/SComponentIterator.h"


float RED[] = { 1.0f, 0.0f, 0.0f };
float BLUE[] = { 0.0f, 0.0f, 1.0f };

std::string Engine::DebugAABB::SystemName()
{
    return std::string();
}

void Engine::DebugAABB::Init()
{
}

void Engine::DebugAABB::Start(CScene* pScene)
{
    for (Entity entityId : SComponentIterator<Rigidbody, AABB>(*pScene))
    {
        Rigidbody* pRigidbody = pScene->Get<Rigidbody>(entityId);
        pRigidbody->gravity = 9.8f;
        pRigidbody->mass = 1.0f;
        pRigidbody->isKinematic = false;
    }
}

void Engine::DebugAABB::Update(CScene* pScene, float deltaTime)
{
    deltaTime = deltaTime / 1000.0f;

    for (Entity entityId : SComponentIterator<Transform, Rigidbody, AABB>(*pScene))
    {
        Transform* pTransform = pScene->Get<Transform>(entityId);
        Rigidbody* pRigidbody = pScene->Get<Rigidbody>(entityId);
        AABB* pAABB = pScene->Get<AABB>(entityId);

        if (!pRigidbody->isKinematic)
        {
            //Vector2 gravityForce = Vector2(0, pRigidbody->gravity * pRigidbody->mass);
            //pTransform->position += gravityForce * deltaTime;

            // Update AABB bounds
            pAABB->CalculateBounds(*pTransform, pAABB->halfSize * 2.0f);
            ResolveCollision(pScene);
        }
    }
}

void Engine::DebugAABB::Render(CScene* pScene)
{

    for (Entity entityId : SComponentIterator<AABB>(*pScene))
    {
     
        
        AABB* pAABB = pScene->Get<AABB>(entityId);
        if (pAABB)
        {
            DebugRectangle(pAABB->minXY, pAABB->maxXY, RED);
        }
       
    }

}

void Engine::DebugAABB::End(CScene* pScene)
{
}

void Engine::DebugAABB::Cleanup()
{
}

void Engine::DebugAABB::DebugRectangle(const Vector2& min, const Vector2& max, const float color[3])
{
    App::DrawLine(min.x, min.y, max.x, min.y, color[0], color[1], color[2]);
    App::DrawLine(max.x, min.y, max.x, max.y, color[0], color[1], color[2]);
    App::DrawLine(max.x, max.y, min.x, max.y, color[0], color[1], color[2]);
    App::DrawLine(min.x, max.y, min.x, min.y, color[0], color[1], color[2]);

}

bool Engine::DebugAABB::CheckCollision(const AABB& a, const AABB& b)
{
    return (a.maxXY.x > b.minXY.x &&
        a.minXY.x < b.maxXY.x &&
        a.maxXY.y > b.minXY.y &&
        a.minXY.y < b.maxXY.y);
}

void Engine::DebugAABB::ResolveCollision(CScene* pScene)
{

    for (Entity entityA : SComponentIterator<Transform, AABB>(*pScene))
    {
        AABB* aabbA = pScene->Get<AABB>(entityA);

        for (Entity entityB : SComponentIterator<Transform, AABB>(*pScene))
        {
            if (entityA == entityB) continue;

            AABB* aabbB = pScene->Get<AABB>(entityB);

            if (CheckCollision(*aabbA, *aabbB))
            {
                // Resolve by moving the entity out of collision (basic response)
                Vector2 overlap = aabbA->center - aabbB->center;
                pScene->Get<Transform>(entityA)->position += overlap * 0.5f;
                pScene->Get<Transform>(entityB)->position -= overlap * 0.5f;
            }
        }
    }


 

}
