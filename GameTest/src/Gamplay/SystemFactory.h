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
        T* CreateSystems(CScene* pScene)
        {
            static_assert(std::is_base_of<iSystems, T>::value, "T must derive from iSystems interface");

            // Create a new system
            T* system = new T();
            mSystems.push_back(system);
            system->Init();
            // Store the system pointer

            return system; // Return the pointer for direct use
        }

        void RemoveSystems(CScene* pScene)
        {
            for (auto it = mSystems.begin(); it != mSystems.end();)
            {
                (*it)->End(pScene);
                (*it)->Cleanup();

                delete* it;              // Delete the system
                it = mSystems.erase(it); // Remove the pointer from the vector
            }
        }

        void Start(CScene* pScene)
        {
            for (iSystems* system : mSystems)
            {
                system->Start(pScene);
            }
        }

        void Update(CScene* pScene, float deltaTime)
        {
            for (iSystems* system : mSystems)
            {
                system->Update(pScene, deltaTime);
            }
        }

        void Render(CScene* pScene)
        {
            for (iSystems* system : mSystems)
            {
                system->Render(pScene);
            }
        }

        void End(CScene* pScene)
        {
            for (iSystems* system : mSystems)
            {
                system->End(pScene);
            }
        }

        void Cleanup()
        {
            for (iSystems* system : mSystems)
            {
                system->Cleanup();
            }
        }

        ~SystemFactory()
        {
            // Ensure all systems are properly deleted
            for (iSystems* system : mSystems)
            {
                delete system;
            }
            mSystems.clear();
        }

    private:
        std::vector<iSystems*> mSystems; // Store raw pointers to systems
    };
}

#endif
