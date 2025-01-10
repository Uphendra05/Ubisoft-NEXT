#pragma once
#include "src/System/iSystems.h"
#include "src/Utilities/Vector2.h"
#include "src/ECS/SComponents.h"
#include "src/Physics/AABB.h"


namespace Engine
{
	class DebugAABB : public iSystems
	{






		// Inherited via iSystems
		std::string SystemName() override;

		void Init() override;

		void Start(CScene* pScene) override;

		void Update(CScene* pScene, float deltaTime) override;

		void Render(CScene* pScene) override;

		void End(CScene* pScene) override;

		void Cleanup() override;

		void AABBDebug(const Vector2& min, const Vector2& max, const float color[3]);

		bool CheckCollision(const AABB& a, const AABB& b);

		void ResolveCollision(CScene* pScene,float deltatime);

	};

}

