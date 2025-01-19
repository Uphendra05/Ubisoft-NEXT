#pragma once
#include "iSystems.h"
#include "src/ECS/SComponents.h"


namespace Engine
{
	class PlayerMovement : public iSystems
	{



	public:

		PlayerMovement() = default;
		virtual ~PlayerMovement() {};


		// Inherited via iSystems
		virtual std::string SystemName() ;

		virtual void Init() ;

		virtual void Start(CScene* pScene) ;

		virtual void Update(CScene* pScene, float deltaTime) ;

		virtual void Render(CScene* pScene) ;

		virtual void End(CScene* pScene) ;

		virtual void Cleanup() ;

		void MoveLeftRight(Transform* pTransform, MovementComponent* pMovement, int direction);

		void MoveUpDown(Transform* pTransform, MovementComponent* pMovement, int direction);

	     void MakeBorders(float& x, float& y);


	};


}
