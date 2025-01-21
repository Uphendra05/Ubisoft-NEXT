#pragma once
#ifndef _FRAMESYSTEM_H
#define _FRAMESYSTEM_H

#include "iSystems.h"
#include "src/ECS/SComponents.h"

//*******************************************************************************************
//  CollisionSysten
//*******************************************************************************************
/* This class is derived from the iSystems interface and updates the FPS for the game

 */

namespace Engine
{
	class FrameSystem :public iSystems		
	{
	public:
		FrameSystem() = default;
		virtual ~FrameSystem() {};

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
