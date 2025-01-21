#pragma once
#ifndef _RENDERSYSTEM_H
#define _RENDERSYSTEM_H

#include "iSystems.h"

#include "src/ECS/SComponents.h"

namespace Engine
{
	class RenderSystem : public iSystems
	{


	public:

		RenderSystem() = default;
		virtual ~RenderSystem() {};

		// Inherited via iSystems
		std::string SystemName() override;

		void Init() override;

		void Start(CScene* pScene) override;

		void Update(CScene* pScene, float deltaTime) override;

		void Render(CScene* pScene) override;

		void End(CScene* pScene) override;

		void Cleanup() override;

	};


}
#endif