#pragma once
#ifndef _CAMERASYSTEM_H
#define _CAMERASYSTEM_H



#include "iSystems.h"
#include "src/ECS/SComponents.h"


namespace Engine
{
    class CameraSystem : public iSystems
    {
        // Inherited via iSystems
        std::string SystemName() override;

        void Init() override;

        void Start(CScene* pScene) override;

        void Update(CScene* pScene, float deltaTime) override;

        void Render(CScene* pScene) override;

        void End(CScene* pScene) override;

        void Cleanup() override;

        Vector2 Lerp(const Vector2& start, const Vector2& end, float t);



        template <typename T>
        T Clamp(const T& value, const T& min, const T& max) {
            if (value < min) {
                return min;
            }
            else if (value > max) {
                return max;
            }
            else {
                return value;
            }
        }
    };

}

#endif
