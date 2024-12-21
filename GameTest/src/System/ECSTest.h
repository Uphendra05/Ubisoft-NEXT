#pragma once
#ifndef _ECSTEST_H
#define _ECSTEST_H

#include "iSystems.h"

namespace Engine
{
    class ECSTest : public iSystems
    {
    public:

        ECSTest() = default;
        virtual ~ECSTest() {};



        // Inherited via iSystems
        std::string SystemName() override;

        void Init() override;

        void Start(CScene* pScene) override;

        void Update(CScene* pScene, float deltaTime) override;

        void Render(CScene* pScene) override;

        void End(CScene* pScene) override;

        void Cleanup() override;

    };


}

#endif