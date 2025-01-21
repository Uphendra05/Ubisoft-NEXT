#pragma once
#ifndef _SCOMPONENTITERATOR_H
#define _SCOMPONENTITERATOR_H

#include "ECSCore.h"
#include "CScene.h"

//*******************************************************************************************
// ComponentIterator
//*******************************************************************************************
/* This is handy method to iterate all the entites with the necessary componenets attached to it
* instead of iterating throught every entity we can find necessary components and check if the entity has the component
* and the find the required entity.

 */



namespace Engine
{
	template<typename... ComponentTypes>
	struct SComponentIterator
	{
		SComponentIterator(CScene& scene)
		{
			mEntityManager = scene.GetEntityManager();


			if (sizeof... (ComponentTypes) == 0)
			{

				mIsParam = true;
			}
			else
			{
				int componentIds[] = { 0, scene.GetComponentType<ComponentTypes>() ... };
				for (int i = 1; i < (sizeof...(ComponentTypes) + 1); i++)
					mMask.set(componentIds[i]);

			}
		}


		struct Iterator
		{
			Iterator(CEntityManager* spriteManager, size_t index, EntityMask mask, bool all ) : mEntityManager(spriteManager), mIndex(index), mMask(mask), mIsParam(all)
			{}

			Entity operator*() const
			{
				return mEntityManager->GetEntities().at(mIndex);
			}

			bool operator==(const Iterator& other) const
			{
				return mIndex == other.mIndex || mIndex == mEntityManager->GetEntities().size();
			}

			bool operator!=(const Iterator& other) const
			{
				return mIndex != other.mIndex || mIndex != mEntityManager->GetEntities().size();
			}

			Iterator& operator++()
			{
				const std::vector<Entity>& entities = mEntityManager->GetEntities();

				do
				{
					mIndex++;
				} while (mIndex < entities.size() && !(mIsParam || mEntityManager->HasComponents(entities[mIndex], mMask)));
					

				return *this;
			}


		private:
			size_t mIndex;
			CEntityManager* mEntityManager{ nullptr };
			EntityMask mMask;
			bool mIsParam{ false };
		};

		const Iterator begin() const
		{
			const std::vector<Entity>& entities = mEntityManager->GetEntities();

			
			size_t firstIndex = 0;
			
			while (firstIndex != entities.size() && !(mIsParam || mEntityManager->HasComponents(entities[firstIndex], mMask)))
				
			{
				firstIndex++;
			}

			return Iterator(mEntityManager, firstIndex, mMask, mIsParam);
		}

		const Iterator end() const
		{
			return Iterator(mEntityManager, mEntityManager->GetEntities().size(), mMask, mIsParam);
		}

	protected:

		bool mIsParam{ false };
		CEntityManager* mEntityManager;
		EntityMask mMask;
	};

}



#endif