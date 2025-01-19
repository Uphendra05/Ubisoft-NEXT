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
		virtual std::string SystemName() ;

		virtual void Init()  ;

		virtual void Start(CScene* pScene) ;

		virtual void Update(CScene* pScene, float deltaTime)  ;

		virtual void Render(CScene* pScene) ;

		virtual void End(CScene* pScene) ;

		virtual void Cleanup() ;

		const float timeStep = 1 / 60.0f;
		float timer = timeStep;


	};

}

