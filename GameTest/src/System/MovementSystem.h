#pragma once
#include "iSystems.h"
#include "src/ECS/SComponents.h"

namespace Engine
{
	class MovementSystem : public iSystems
	{


	public:

		MovementSystem() = default;
		virtual ~MovementSystem() {};

		// Inherited via iSystems
		std::string SystemName() override;

		void Init()  override;

		void Start(CScene* pScene) override;

		void Update(CScene* pScene, float deltaTime)  override;

		void Render(CScene* pScene) override;

		void End(CScene* pScene) override;

		void Cleanup() override;

	};

}

