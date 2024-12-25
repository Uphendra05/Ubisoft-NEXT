#pragma once
#ifndef _SSPRITEMANAGER_H
#define _SSPRITEMANAGER_H
#include "App/app.h"
#include <unordered_map>

#include "src/ECS/ECSCore.h"
#include "src/ECS/SComponents.h"

namespace Engine
{

	class CSpriteManager
	{

	public:
		CSpriteManager() {};
		~CSpriteManager() {};


		void AttachSprite(Entity entity, SpriteRenderer& sprite, Transform& transform );
		void RemoveSprite();

		void AddAnimation();
		void UpdateAnimation();

		CSimpleSprite GetSprite();


		void Update(float dt);
		void Render();
		void CleanUp();


	private:

		CSimpleSprite* CreateSprite(const std::string filename, int rows, int cols);

		std::unordered_map<std::string, CSimpleSprite*> mSpriteCache;

		std::unordered_map<Entity, CSimpleSprite*> mEntitySprites;
	};

}

#endif

