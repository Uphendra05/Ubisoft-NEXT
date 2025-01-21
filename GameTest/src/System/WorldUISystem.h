#pragma once
#ifndef _WORLDUI_H
#define _WORLDUI_H


#include "src/System/iSystems.h"


namespace Engine
{
	class WorldUISystem : public iSystems
	{
	public :
		WorldUISystem() = default;
		virtual ~WorldUISystem() {};


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

