#pragma once
#include "iSystems.h"
#include "src/ECS/SComponents.h"

#include "src/Events/CollisionEvent.h"

namespace Engine
{
	class PlayerHealthSystem :public iSystems		
	{
	public:
		PlayerHealthSystem() = default;
		virtual ~PlayerHealthSystem() {};

		// Inherited via iSystems
		virtual std::string SystemName() ;

		virtual void Init() ;

		virtual void Start(CScene* pScene) ;

		virtual void Update(CScene* pScene, float deltaTime) ;

		virtual void Render(CScene* pScene) ;

		virtual void End(CScene* pScene) ;

		virtual void Cleanup() ;

		static void OnCollision(const CollisionEnterEvent& event);
	};

}

