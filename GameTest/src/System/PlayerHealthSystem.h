#pragma once
#include "iSystems.h"
#include "src/ECS/SComponents.h"

#include "src/Events/CollisionEvent.h"

namespace Engine
{
	class PlayerHealthSystem :public iSystems		
	{
	public:
		PlayerHealthSystem() = default;
		virtual ~PlayerHealthSystem() {};

		// Inherited via iSystems
		std::string SystemName() override;

		void Init() override;

		void Start(CScene* pScene) override;

		void Update(CScene* pScene, float deltaTime) override;

		void Render(CScene* pScene) override;

		void End(CScene* pScene) override;

		void Cleanup() override;

		static void OnCollision(const CollisionEnterEvent& event);
	};

}

