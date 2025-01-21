#pragma once
#include "src/System/iSystems.h"
#include "src/Gamplay/Enums.h"

namespace Engine
{
	class LevelModifier :public iSystems
	{
		// Inherited via iSystems
		std::string SystemName() override;

		void Init() override;

		void Start(CScene* pScene) override;

		void Update(CScene* pScene, float deltaTime) override;

		void Render(CScene* pScene) override;

		void End(CScene* pScene) override;

		void Cleanup() override;

	private:

		void DecideLevelModifier(CScene* pScene, float deltaTime);

		eLevelModifiers mLevelModifier = eLevelModifiers::NIL;

		const std::vector<eLevelModifiers> modifiers = 
		{
		   UNPREDTICTABLEMOVE,
		   RIGIDMOVEMENT,
		   FOGOFWAR
		};

		bool isModified = false;




	};

}

