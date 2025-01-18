#pragma once
#ifndef _COLLISIONSYSTEM_H
#define _COLLISIONSYSTEM_H


#include "src/System/iSystems.h"
#include "src/Utilities/Vector2.h"
#include "src/ECS/SComponents.h"
#include "src/Physics/AABB.h"
#include "src/Events/CollisionEvent.h"
#include "src/Events/iEventBus.h"


namespace Engine
{
	class CollisionSystem : public iSystems
	{


	public:

		CollisionSystem() = default;
		virtual ~CollisionSystem() {};

		// Inherited via iSystems
		std::string SystemName() override;

		void Init() override;

		void Start(CScene* pScene) override;

		void Update(CScene* pScene, float deltaTime) override;

		void Render(CScene* pScene) override;

		void End(CScene* pScene) override;

		void Cleanup() override;

		void AABBDebug(const Vector2& min, const Vector2& max, const float color[3]);

		bool CheckCollision(const sAABB& a, const sAABB& b);

		void ResolveCollision(CScene* pScene,float deltatime);

		void CreateAABB(Entity entityID, Rigidbody* pRb, Transform* pTransform, CScene* pScene);

		bool FrameCollision(const sCollisionData& collData);

		void TriggerCollision(const sCollisionData& collData);

		Vector2 ComputeNormals(std::vector<Vector2> collisionNormals);

	
		iEventBus<eCollisionEvents, CollisionEnterEvent>* m_pEventBusCollision;
		
		std::vector<Vector2> collisionNormals;

		
	};

}
#endif

