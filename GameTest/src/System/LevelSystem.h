#pragma once
#include "iSystems.h"
#include "src/Events/GameStateEvent.h"
#include "src/Events/CollisionEvent.h"
#include "src/Events/iEventBus.h"
#include "src/Gamplay/Enums.h"


namespace Engine
{
	class LevelSystem :public iSystems		
	{
	public:

		// Inherited via iSystems
		std::string SystemName() override;

		void Init() override;

		void Start(CScene* pScene) override;

		void Update(CScene* pScene, float deltaTime) override;

		void Render(CScene* pScene) override;

		void End(CScene* pScene) override;

		void Cleanup() override;

	private:

		static void OnStart(const GameStartedEvent& event);

		static void OnRunning(const GameRunningEvent& event);

		static void OnNewLevel(const GameNewLevelEvent& event);

		static void OnGameOver(const GameOverEvent& event);


		static void LevelOne(const GameRunningEvent& event);

		static void LevelTwo(const GameNewLevelEvent& event);




	};
}


