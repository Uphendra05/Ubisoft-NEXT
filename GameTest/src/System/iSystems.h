#pragma once
#ifndef _ISYSTEMS_H
#define _ISYSTEMS_H

#include "src/ECS/ECSCore.h"
#include "src/ECS/CScene.h"

namespace Engine
{

	class iSystems
	{

	public:
		iSystems() = default;
		virtual ~iSystems() { };

		virtual std::string SystemName() = 0;

		virtual void Init() = 0;

		virtual void Start(CScene* pScene) = 0;

		virtual void Update(CScene* pScene, float deltaTime) = 0;

		virtual void Render(CScene* pScene) = 0;

		virtual void End(CScene* pScene) = 0;

		virtual void Cleanup() = 0;



	};



}


#endif