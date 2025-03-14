#include "stdafx.h"
#include "CameraSystem.h"
#include "src/ECS/SComponentIterator.h"
#include "src/Utilities/GamplayUtils.h"
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
	
	Entity player = pScene->GetEntityManager()->GetEntity(1);
	Entity camera = pScene->GetEntityManager()->GetEntity(4);

	if (!player || !camera) return;

	Transform* playerTransform = pScene->GetComponent<Transform>(player);
	CameraComponent* cameraComp = pScene->GetComponent<CameraComponent>(camera);

		if(playerTransform && cameraComp)
		{ 

			
			Vector2 targetPosition = playerTransform->position;
			cameraComp->position = Lerp(cameraComp->position, targetPosition, 0.1f);

			// Clamp camera position to bounds (if applicable)
			//cameraComp->position.x = std::clamp(cameraComp->position.x, 0.0f,  cameraComp->width);
			//cameraComp->position.y = std::clamp(cameraComp->position.y, 0.0f,   cameraComp->height );

			// Update the transform for the camera entity
			Transform* cameraTransform = pScene->GetComponent<Transform>(camera);
			if (cameraTransform)
			{
				cameraTransform->position = cameraComp->position;
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


