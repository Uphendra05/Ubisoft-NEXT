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
			AddAnimation(&sprite);
		}
	}

	void Engine::CSpriteManager::RemoveSprite()
	{

	}

	void Engine::CSpriteManager::AddAnimation(SpriteRenderer* sprite)
	{

		if (sprite->rows > 1 || sprite->cols > 1)
		{
			int frame = 0;
			for (int i = 0; i < sprite->rows; i++)
			{
				std::vector<int> animationFrames;

				for (int j = 0; j < sprite->cols; j++)
				{
					animationFrames.push_back(frame++);
				}

				GetSprite(sprite->fileName)->CreateAnimation(i, sprite->animSpeed, animationFrames);
				

			}
		}
		

	}

	void Engine::CSpriteManager::UpdateAnimation()
	{
	}

	CSimpleSprite* CSpriteManager::GetSprite(const std::string filename)
	{
		return mSpriteCache[filename];
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

