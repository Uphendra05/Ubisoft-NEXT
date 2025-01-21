#include "stdafx.h"
#include "RaycastSystem.h"
#include "src/ECS/SComponentIterator.h"
#include "src/Utilities/MathUtils.hpp"

namespace Engine
{
	float RED[] = { 1.0f, 0.0f, 0.0f };
	const Entity INVALID_ENTITY = -1;
	const float POSITIONX = 200.0f;
	const float POSITIONY = 600.0f;
	std::string UITEXT = " I ";
	const float COLOR[3] = { 1.0f, 1.0f, 1.0f };


	std::string Engine::RaycastSystem::SystemName()
	{
		return std::string();
	}

	void Engine::RaycastSystem::Init()
	{
	}

	void Engine::RaycastSystem::Start(CScene* pScene)
	{
		for (Entity entityID : SComponentIterator<RaycastComponent>(*pScene))
		{
			RaycastComponent* pRay = pScene->GetComponent<RaycastComponent>(entityID);
			pRay->origin = Vector2(400.0f, 600.0f); // Starting position
			pRay->direction = Vector2(1, 0).normalized(); // Direction (right)
			pRay->length = 500.0f;

		}
	}

	void Engine::RaycastSystem::Update(CScene* pScene, float deltaTime)
	{
		for (Entity entityID : SComponentIterator<RaycastComponent>(*pScene))
		{
			RaycastComponent* pRay = pScene->GetComponent<RaycastComponent>(entityID);

			float hitDistance;
			Entity outEntity;
			bool hitEntity = Raycast(pScene, *pRay, hitDistance, outEntity);

			if (hitEntity)
			{
				
				UITEXT = "Entity HIT !";

			}
			else
			{
				UITEXT = " !";
			}
		}
	}

	void Engine::RaycastSystem::Render(CScene* pScene)
	{

#ifdef _DEBUG
		for (Entity entityId : SComponentIterator<sAABB>(*pScene))
		{


			RaycastComponent* pRay = pScene->GetComponent<RaycastComponent>(entityId);
			if (pRay)
			{
				DebugRay(*pRay,RED);
			}

		}
		App::Print(POSITIONX, POSITIONY, UITEXT.c_str(), COLOR[0], COLOR[1], COLOR[2]);
#endif

	}

	void Engine::RaycastSystem::End(CScene* pScene)
	{
	}

	void Engine::RaycastSystem::Cleanup()
	{
	}

	bool RaycastSystem::Raycast(CScene* pScene, const RaycastComponent& ray, float& outDistance, Entity& outEntity)
	{
		bool hit = false;
		outDistance = ray.length;
		outEntity = INVALID_ENTITY;

		for (Entity entity : SComponentIterator<sAABB>(*pScene))
		{
			sAABB* aabb = pScene->GetComponent<sAABB>(entity);
			float hitDistance;

			if (aabb && CheckRayVsAABB(ray, *aabb, hitDistance) && hitDistance < outDistance)
			{
				outDistance = hitDistance;
				outEntity = entity;
				hit = true;
			}
		}

		return hit;
	}



	bool Engine::RaycastSystem::CheckRayVsAABB(const RaycastComponent& ray, const sAABB& aabb, float& outDistance)
	{
		float tMin = 0.0f;
		float tMax = ray.length;

		for (int i = 0; i < 2; ++i) // X and Y axes
		{
			float rayOrigin = (i == 0) ? ray.origin.x : ray.origin.y;
			float rayDir = (i == 0) ? ray.direction.x : ray.direction.y;
			float boxMin = (i == 0) ? aabb.minXY.x : aabb.minXY.y;
			float boxMax = (i == 0) ? aabb.maxXY.x : aabb.maxXY.y;

			if (rayDir != 0.0f)
			{
				float invDir = 1.0f / rayDir;
				float t1 = (boxMin - rayOrigin) * invDir;
				float t2 = (boxMax - rayOrigin) * invDir;

				if (t1 > t2) std::swap(t1, t2);

				tMin = MathUtils::Max(tMin, t1);
				tMax = MathUtils::Min(tMax, t2);

				if (tMin > tMax) return false; // No intersection
			}
			else if (rayOrigin < boxMin || rayOrigin > boxMax)
			{
				return false; // Ray is parallel and outside the AABB
			}
		}

		outDistance = tMin;
		return true;
	}

	void Engine::RaycastSystem::DebugRay(const RaycastComponent& ray, const float color[3])
	{
		Vector2 endPoint = ray.origin + ray.direction * ray.length;
		App::DrawLine(ray.origin.x, ray.origin.y, endPoint.x, endPoint.y, color[0], color[1], color[2]);

	}


}
