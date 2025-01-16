#pragma once
#include "src/ECS/SComponents.h"
#include "src/ECS/CScene.h"
namespace Engine
{
	class GraphicUtils
	{

	public:

		static void UpdateAnimation(SpriteRenderer* pSprite, Transform* pTransform, const float& deltaTime);

		// Creates the animations and frames for the sprite based on the cols and rows given
		static void CreateAnimation(SpriteRenderer* pSprite);

		// Creates sprite using API and updates, setting up everything needed for the sprite
		static void SetupSprite(SpriteRenderer* pSprite, Transform* pTransform);

		static void DrawSprite(SpriteRenderer* pSprite);

		static void CreateUIWidget();

		

	


	};


}


