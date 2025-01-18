#include "stdafx.h"
#include "PlayerHealthSystem.h"
#include "src/Events/EventBus.hpp"
#include "src/Events/EventBusLocator.hpp"


std::string Engine::PlayerHealthSystem::SystemName()
{
    return std::string();
}

void Engine::PlayerHealthSystem::Init()
{
}

void Engine::PlayerHealthSystem::Start(CScene* pScene)
{
    // Subscribe to enter collision event
    iEventBus<eCollisionEvents, CollisionEnterEvent>* pEventBus = EventBusLocator<eCollisionEvents, CollisionEnterEvent>::Get();

    pEventBus->Subscribe(eCollisionEvents::ONCOLLISION_ENTER, OnCollision);
}

void Engine::PlayerHealthSystem::Update(CScene* pScene, float deltaTime)
{

}

void Engine::PlayerHealthSystem::Render(CScene* pScene)
{
}

void Engine::PlayerHealthSystem::End(CScene* pScene)
{
    iEventBus<eCollisionEvents, CollisionEnterEvent>* pEventBus = EventBusLocator<eCollisionEvents, CollisionEnterEvent>::Get();

    pEventBus->Unsubscribe(eCollisionEvents::ONCOLLISION_ENTER, OnCollision);
}

void Engine::PlayerHealthSystem::Cleanup()
{
}

void Engine::PlayerHealthSystem::OnCollision(const CollisionEnterEvent& event)
{
    CScene* pScene = event.collisionData.pScene;
    Entity entityActive = event.collisionData.entityA;
    Entity entityPassive = event.collisionData.entityB;

    SpriteRenderer* pSprite = pScene->GetComponent<SpriteRenderer>(entityActive);
    pSprite->sprite = new CSimpleSprite("D:/Git Repos/Ubisoft_Next/Ubisoft-NEXT/GameTest/Assets/Red.png", 1, 1);


}
