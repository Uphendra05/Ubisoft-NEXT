#include "stdafx.h"
#include "RenderSystem.h"
#include "src/ECS/SComponentIterator.h"
#include "src/Utilities/GraphicUtils.h"

namespace Engine
{

    std::string Engine::RenderSystem::SystemName()
    {
        return std::string();
    }

    void Engine::RenderSystem::Init()
    {
    }

    void Engine::RenderSystem::Start(CScene* pScene)
    {
        for (Entity entityId : SComponentIterator<Transform, SpriteRenderer>(*pScene))
        {
            Transform* pTransform = pScene->Get<Transform>(entityId);
            SpriteRenderer* pSprite = pScene->Get<SpriteRenderer>(entityId);

            if (pSprite)
            {
                continue;
            }

            GraphicUtils::SetupSprite(pSprite, pTransform);



            
        }
        return;

    }

    void Engine::RenderSystem::Update(CScene* pScene, float deltaTime)
    {
        for (Entity entityId : SComponentIterator<Transform, SpriteRenderer>(*pScene))
        {
            Transform* pTransform = pScene->Get<Transform>(entityId);
            SpriteRenderer* pSprite = pScene->Get<SpriteRenderer>(entityId);

            GraphicUtils::UpdateAnimation(pSprite, pTransform, deltaTime);

        }
    }

    void Engine::RenderSystem::Render(CScene* pScene)
    {
        for (Entity entityId : SComponentIterator<SpriteRenderer>(*pScene))
        {
            SpriteRenderer* pSprite = pScene->Get<SpriteRenderer>(entityId);


            GraphicUtils::DrawSprite(pSprite);



        }
    }

    void Engine::RenderSystem::End(CScene* pScene)
    {
    }

    void Engine::RenderSystem::Cleanup()
    {
    }
}

