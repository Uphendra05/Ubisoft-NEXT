#include "stdafx.h"
#include "GamplayUtils.h"

#include "src/ECS\SComponents.h"
#include "src/Gamplay/CSpriteManager.h"



namespace Engine
{

	// TODO : Should this be here ? should I create a sprite system and handle the sprite assignment through that ?
	CSpriteManager spriteManager;

	Entity Engine::GamplayUtils::CreateECSTEST(CScene* pScene, Vector2 position)
	{
		Entity ECSTestId = pScene->CreateEntity();
		Transform* pTransform = pScene->AddComponent<Transform>(ECSTestId);
		pTransform->position = position;
		pTransform->rotation = 35;
		pTransform->scale = 3;

		return ECSTestId;
	}


	Entity GamplayUtils::CreateBackground(CScene* pScene, Vector2 position)
	{
		Entity backgroundId = pScene->CreateEntity();
		Transform* pTransform = pScene->AddComponent<Transform>(backgroundId);
		pTransform->position = position;
		pTransform->rotation = 0;
		pTransform->scale = 1;

		SpriteRenderer* pSprite = pScene->AddComponent<SpriteRenderer>(backgroundId);
		pSprite->fileName = "D:/Git Repos/Ubisoft_Next/Ubisoft-NEXT/GameTest/Assets/Backgroound.png";
		pSprite->cols = 1;
		pSprite->rows = 1;

		spriteManager.AttachSprite(backgroundId, *pSprite, *pTransform);

		return backgroundId;

	}
	void GamplayUtils::Update(float dt)
	{

		spriteManager.Update(dt);
	}
	void GamplayUtils::Render()
	{

		spriteManager.Render();
	}
	void GamplayUtils::CleanUp()
	{
		spriteManager.CleanUp();
	}
}
