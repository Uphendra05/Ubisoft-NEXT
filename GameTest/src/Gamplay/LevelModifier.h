#pragma once
#ifndef _LEVELMODIFIER_H
#define _LEVELMODIFIER_H

#include "src/System/iSystems.h"
#include "src/Gamplay/Enums.h"

//*******************************************************************************************
//  LevelModifier
//*******************************************************************************************
/* This class is for creating random modifiers for the level when the player starts to play the game
you can add n number of modifiers here and it will give you a random modifier when the level starts.

 */

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

#endif