#pragma once
#ifndef _SYSTEMFACTORY_H
#define _SYSTEMFACTORY_H

#include "src/System/iSystems.h"
#include "src/ECS/CScene.h"

namespace Engine
{
	class SystemFactory
	{
		
	public:

		template <typename T>
		std::shared_ptr<iSystems> CreateSystems()
		{
			static_assert(std::is_base_of<iSystems, T>::value, "T must derive from iSystems interface"); // To ensure only types derived from iSystems can be created.

			std::shared_ptr<iSystems> system = std::make_shared<T>();
			system->Init();

			std::shared_ptr<iSystems> baseSystem = std::static_pointer_cast<iSystems>(system);
			mSystems.push_back(baseSystem);

			return baseSystem;
		}

		inline void RemoveSystems(CScene* pScene)
		{

			for (size_t i = 0; i < mSystems.size(); i++)
			{
				if (mSystems.size() == 0)
				{
					continue;
				}

				mSystems[i]->End(pScene);
				mSystems[i]->Cleanup();
				mSystems.erase(mSystems.begin() + i);


			}


		}

		inline void Start(CScene* pScene)
		{
			for (std::shared_ptr<iSystems>& system : mSystems)
			{
				system->Start(pScene);
			}
		}



		inline void Update(CScene* pScene, float deltaTime)
		{
			for (std::shared_ptr<iSystems>& system : mSystems)
			{
				if (system == nullptr)
				{
					continue;
				}

				system->Update(pScene, deltaTime);
			}
		}

		inline void Render(CScene* pScene)
		{
			for (std::shared_ptr<iSystems>& system : mSystems)
			{
				system->Render(pScene);
			}
		}



		inline void End(CScene* pScene)
		{
			for (std::shared_ptr<iSystems>& system : mSystems)
			{
				system->End(pScene);
			}
		}

		inline void Cleanup()
		{
			for (std::shared_ptr<iSystems>& system : mSystems)
			{
				system->Cleanup();
			}

		}




	private:

		std::vector<std::shared_ptr<iSystems>> mSystems;

	
    };
}

#endif
