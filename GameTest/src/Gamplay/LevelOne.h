#pragma once
#ifndef _LEVELONE_H
#define _LEVELONE_H

#include "src/System/iSystems.h"
#include "src/Gamplay/Enums.h"

#include "src/Events/CollisionEvent.h"

namespace Engine
{
    class LevelOne : public iSystems       
    {

    public:

        LevelOne() = default;
        virtual ~LevelOne() {};



        // Inherited via iSystems
        std::string SystemName() override;

        void Init() override;

        void Start(CScene* pScene) override;

        void Update(CScene* pScene, float deltaTime) override;

        void Render(CScene* pScene) override;

        void End(CScene* pScene) override;

        void Cleanup() override;

    private:


       

       static void OnCollision(const CollisionEnterEvent& event);

        size_t mObjectivePoints = 0;
        size_t mMultiplier = 0;
        size_t mStrokes = 0;
        size_t mMaxStrokes = 6;

        float timer = 0.0f;

        eGameStreaks mGameStreaks = eGameStreaks::ZERO;


    };


}
#endif
