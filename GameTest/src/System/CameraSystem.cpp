#include "stdafx.h"
#include "CameraSystem.h"
#include "src/ECS/SComponentIterator.h"
#include "src/Utilities/GamplayUtils.h"
#include <iostream> 
#include <algorithm>



std::string Engine::CameraSystem::SystemName()
{
	return std::string();
}

void Engine::CameraSystem::Init()
{
}

void Engine::CameraSystem::Start(CScene* pScene)
{
}

void Engine::CameraSystem::Update(CScene* pScene, float deltaTime)
{
	for (Entity entityId : SComponentIterator<Transform, CameraComponent>(*pScene))
	{
		Transform* pTransform = pScene->Get<Transform>(entityId);
		CameraComponent* pCamera = pScene->Get<CameraComponent>(entityId);

		if(pTransform && pCamera)
		{ 
			Vector2 targetPosition = pTransform->position;
			pCamera->position = Lerp(pCamera->position, targetPosition, 0.1f);

			// Clamp camera position to bounds (if applicable)
			//pCamera->position.x = std::clamp(pCamera->position.x, 0.0f, APP_VIRTUAL_WIDTH - pCamera->width);
			//pCamera->position.y = std::clamp(pCamera->position.y, 0.0f, APP_VIRTUAL_HEIGHT - pCamera->height);

			// Update the transform for the camera entity
			Transform* cameraTransform = pScene->Get<Transform>(entityId);
			if (cameraTransform)
			{
				cameraTransform->position = pCamera->position;
			}

		
		}

	}

}

void Engine::CameraSystem::Render(CScene* pScene)
{
}

void Engine::CameraSystem::End(CScene* pScene)
{
}

void Engine::CameraSystem::Cleanup()
{
}

Engine::Vector2 Engine::CameraSystem::Lerp(const Vector2& start, const Vector2& end, float t)
{
	return start + (end - start) * t;
}


