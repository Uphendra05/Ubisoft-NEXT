#include "stdafx.h"
#include "CSpriteManager.h"



namespace Engine
{
	void Engine::CSpriteManager::AttachSprite(Entity entity, SpriteRenderer& sprite, Transform& transform)
	{

		CSimpleSprite* pSprite = CreateSprite(sprite.fileName, sprite.rows, sprite.cols);
		mEntitySprites[entity] = pSprite;
		if (pSprite)
		{
			pSprite->SetPosition(transform.position.x, transform.position.y);
			pSprite->SetAnimation(0);
		}
	}

	void Engine::CSpriteManager::RemoveSprite()
	{

	}

	void Engine::CSpriteManager::AddAnimation()
	{
	}

	void Engine::CSpriteManager::UpdateAnimation()
	{
	}

	void CSpriteManager::Update(float dt)
	{
		for (auto& pair : mEntitySprites)
		{
			pair.second->Update(dt);
		}
	}

	void CSpriteManager::Render()
	{
		for (auto& pair : mEntitySprites)
		{
			pair.second->Draw();
		}
	}

	void Engine::CSpriteManager::CleanUp()
	{

		for (auto& pair : mSpriteCache)
		{
			delete pair.second;
		}

		mSpriteCache.clear();
		mEntitySprites.clear();
	}




	CSimpleSprite* CSpriteManager::CreateSprite(const std::string filename, int rows, int cols)
	{
		std::string key = filename;

		// Check if the sprite already exists in the cache
		if (mSpriteCache.find(key) == mSpriteCache.end())
		{
			// Create the sprite and store it in the cache
			CSimpleSprite* newSprite = App::CreateSprite(filename.c_str(), cols, rows);
			mSpriteCache[key] = newSprite;
		}

		return mSpriteCache[key];
	}
}
