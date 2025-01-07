#include "stdafx.h"
#include "ECSTest.h"
#include "src/ECS/SComponentIterator.h"
#include "src/ECS/SComponents.h"

std::string Engine::ECSTest::SystemName()
{
    return "ECSTEST SYSTEM";
}

void Engine::ECSTest::Init()
{

}

void Engine::ECSTest::Start(CScene* pScene)
{

}

void Engine::ECSTest::Update(CScene* pScene, float deltaTime)
{
    for (Entity entityId : SComponentIterator<Transform>(*pScene))
    {
        Transform* pTransform = pScene->Get<Transform>(entityId);

        pTransform->worldPosition = pTransform->position;
        pTransform->worldrotation = pTransform->rotation;
        pTransform->worldScale = pTransform->scale;

    }
}

void Engine::ECSTest::Render(CScene* pScene)
{
}

void Engine::ECSTest::End(CScene* pScene)
{
}

void Engine::ECSTest::Cleanup()
{
}
