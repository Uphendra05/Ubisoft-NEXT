#pragma once
#ifndef _SHUFFLEHOLESYSTEM_H
#define _SHUFFLEHOLESYSTEM_H

#include "iSystems.h"
#include "src/ECS/SComponents.h"

namespace Engine
{
	class ShuffleHoleSystem :public iSystems
	{

	public:
		ShuffleHoleSystem() = default;
		virtual ~ShuffleHoleSystem() {};

		// Inherited via iSystems
		std::string SystemName() override;

		void Init() override;

		void Start(CScene* pScene) override;

		void Update(CScene* pScene, float deltaTime) override;

		void Render(CScene* pScene) override;

		void End(CScene* pScene) override;

		void Cleanup() override;

	private :

		void ShufflePositions(CScene* pScene, std::vector<Entity>& entities);
		std::vector<Entity> movableEntities;

	};

}

#endif