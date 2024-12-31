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

		void AddAnimation(SpriteRenderer* sprite);
		void UpdateAnimation();

		CSimpleSprite* GetSprite(const std::string filename);


		void Update(float dt);
		void Render();
		void CleanUp();


	private:

		CSimpleSprite* CreateSprite(const std::string filename, int rows, int cols);

		// Cache of shared sprites by name and configuration
		std::unordered_map<std::string, CSimpleSprite*> mSpriteCache;

		// Mapping from entities to sprites
		std::unordered_map<Entity, CSimpleSprite*> mEntitySprites;
	};

}

#endif

