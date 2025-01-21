#pragma once
#include "src/System/iSystems.h"
#include "src/Gamplay/Enums.h"

#include "src/Events/CollisionEvent.h"

namespace Engine
{
	class LevelTwo :public iSystems		
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


		static void OnCollision(const CollisionEnterEvent& event);

		size_t mObjectivePoints = 0;
		size_t mMultiplier = 0;
		size_t mStrokes;
		size_t mMaxStrokes = 6;

		float timer;
		eGameStreaks mGameStreaks;

	};
}


