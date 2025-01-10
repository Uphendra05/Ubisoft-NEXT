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
        Entity cameraEntity = pScene->GetEntityManager()->GetEntity(4);

        if (cameraEntity)
        {
            CameraComponent* camera = pScene->Get<CameraComponent>(cameraEntity);

            Vector2 cameraOffset = camera ? camera->position : Vector2(0, 0);

            for (Entity entity : SComponentIterator<Transform, SpriteRenderer>(*pScene))
            {
                Transform* transform = pScene->Get<Transform>(entity);
                SpriteRenderer* sprite = pScene->Get<SpriteRenderer>(entity);

                if (transform && sprite)
                {
                    Vector2 screenPosition = transform->position - cameraOffset;
                    sprite->sprite->SetPosition(screenPosition.x, screenPosition.y);

                    GraphicUtils::DrawSprite(sprite);
                }
            }
        }
        
        
    }

    void Engine::RenderSystem::End(CScene* pScene)
    {
    }

    void Engine::RenderSystem::Cleanup()
    {
    }
}

