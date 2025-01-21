#pragma once
#ifndef _RAYCASTSYSTEM_H
#define _RAYCASTSYSTEM_H

#include "iSystems.h"
#include <iostream>
#include "src/ECS/SComponents.h"
#include "src/Physics/AABB.h"

namespace Engine
{
	class RaycastSystem :public iSystems
	{


		public:

		RaycastSystem() = default;
		virtual ~RaycastSystem() {};

		// Inherited via iSystems
		std::string SystemName() override;

		void Init() override;

		void Start(CScene* pScene) override;

		void Update(CScene* pScene, float deltaTime) override;

		void Render(CScene* pScene) override;

		void End(CScene* pScene) override;

		void Cleanup() override;

		bool Raycast(CScene* pScene, const RaycastComponent& ray, float& outDistance, Entity& outEntity); //should I have bool has my data type ?

		bool CheckRayVsAABB(const RaycastComponent& ray, const sAABB& aabb, float& outDistance);

		void DebugRay(const RaycastComponent& ray, const float color[3]);

		
		
	};
}
#endif
