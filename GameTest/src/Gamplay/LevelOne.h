#pragma once
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

        size_t CalculateResult(size_t strokes, size_t points, size_t multiplier);
        size_t PointStreaks(size_t strokes, size_t multiplier);

       static void OnCollision(const CollisionEnterEvent& event);

        size_t mObjectivePoints = 0;
        size_t mMultiplier = 0;
         size_t mStrokes;
        size_t mMaxStrokes = 6;

        size_t timer;
        eGameStreaks mGameStreaks;


    };


}

