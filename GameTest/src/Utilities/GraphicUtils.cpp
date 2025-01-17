#include "stdafx.h"
#include "GraphicUtils.h"


void Engine::GraphicUtils::UpdateAnimation(SpriteRenderer* pSprite, Transform* pTransform, const float& deltaTime)
{
    if (!pSprite->isStatic)
    {
        pSprite->sprite->SetPosition(pTransform->position.x, pTransform->position.y);
        pSprite->sprite->SetAngle(pTransform->rotation);
        pSprite->sprite->SetScale(pTransform->scale);

        pSprite->sprite->Update(deltaTime);
    }
   
}

void Engine::GraphicUtils::CreateAnimation(SpriteRenderer* pSprite)
{
    int frame = 0;
    for (int i = 0; i < pSprite->rows; i++)
    {
        std::vector<int> animationFrames;

        for (int j = 0; j < pSprite->cols; j++) {
            animationFrames.push_back(frame++);
        }

        pSprite->sprite->CreateAnimation(i, pSprite->animSpeed, animationFrames);
    }
}

void Engine::GraphicUtils::SetupSprite(SpriteRenderer* pSprite, Transform* pTransform)
{
    pSprite->sprite = App::CreateSprite(pSprite->fileName.c_str(), pSprite->cols, pSprite->rows);
    UpdateAnimation(pSprite, pTransform, 0.1f);

   // CreateAnimation(pSprite);

    //pSprite->sprite->SetAnimation(0);

    return;
}

void Engine::GraphicUtils::DrawSprite(SpriteRenderer* pSprite)
{
    if (pSprite->sprite)
    {
        pSprite->sprite->Draw();
    }
}

