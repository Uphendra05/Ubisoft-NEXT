#include "stdafx.h"
#include "GamplayUtils.h"

#include "src/ECS\SComponents.h"

namespace Engine
{
	Entity Engine::GamplayUtils::CreateECSTEST(CScene* pScene, Vector2 position)
	{
		Entity ECSTestId = pScene->CreateEntity(true);
		Transform* pTransform = pScene->AddComponent<Transform>(ECSTestId);
		pTransform->position = position;
		pTransform->rotation = 35;
		pTransform->scale = 3;

		return ECSTestId;
	}
}

