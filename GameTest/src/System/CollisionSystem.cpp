#include "stdafx.h"
#include "CollisionSystem.h"

#include "App/app.h"
#include "src/ECS/SComponentIterator.h"
#include "src/Utilities/PlayerUtilities.h"
#include "src/Utilities/ComponentUtils.h"
#include "src/Events/EventBus.hpp"
#include "src/Events/EventBusLocator.hpp"

const float POSITIONX = 400.0f;
const float POSITIONY = 600.0f;
std::string FRAMECOLTEXT = " I ";

const float HEALTHPOSITIONX = 200.0f;
const float HEALTHPOSITIONY = 600.0f;
std::string HEALTHTEXT = " HEa ";



const float COLOR[3] = { 1.0f, 1.0f, 1.0f };



float BLUE[] = { 0.0f, 0.0f, 1.0f };

std::string Engine::CollisionSystem::SystemName()
{
    return std::string();
}

void Engine::CollisionSystem::Init()
{
    m_pEventBusCollision = new EventBus<eCollisionEvents, CollisionEnterEvent>();
    EventBusLocator<eCollisionEvents, CollisionEnterEvent>::Set(m_pEventBusCollision);
}

void Engine::CollisionSystem::Start(CScene* pScene)
{
    for (Entity entityId : SComponentIterator<Rigidbody, Transform>(*pScene))
    {
        Transform* pTransform = pScene->GetComponent<Transform>(entityId);
        Rigidbody* pRigidbody = pScene->GetComponent<Rigidbody>(entityId);

        pRigidbody->gravity = 9.8f;
        pRigidbody->mass = 1.0f;
        pRigidbody->isKinematic = false;


        CreateAABB(entityId, pRigidbody, pTransform,pScene);
    }

    for (Entity entityId : SComponentIterator<HealthComponent>(*pScene))
    {
        HealthComponent* pHealth = pScene->GetComponent<HealthComponent>(entityId);

        pHealth->currentHealth = 150;
        pHealth->maxHealth = 150;

    }
}

void Engine::CollisionSystem::Update(CScene* pScene, float deltaTime)
{
    deltaTime = deltaTime / 1000.0f;
 

    for (Entity entityId : SComponentIterator<Transform, Rigidbody, sAABB>(*pScene))
    {
        Transform* pTransform = pScene->GetComponent<Transform>(entityId);
        Rigidbody* pRigidbody = pScene->GetComponent<Rigidbody>(entityId);
        sAABB* pAABB = pScene->GetComponent<sAABB>(entityId);
       
        if (!pRigidbody->isKinematic)
        {
            //Vector2 gravityForce = Vector2(0, pRigidbody->gravity * pRigidbody->mass);
            //pTransform->position += gravityForce * deltaTime;

            
            // Update AABB bounds
            pAABB->CalculateBounds(*pTransform, pAABB->halfSize * 2.0f);

            
            ResolveCollision(pScene, deltaTime);
        }
    }
}

void Engine::CollisionSystem::Render(CScene* pScene)
{
#ifdef _DEBUG
    for (Entity entityId : SComponentIterator<sAABB>(*pScene))
    {
     
        
        sAABB* pAABB = pScene->GetComponent<sAABB>(entityId);
        if (pAABB)
        {
            AABBDebug(pAABB->minXY, pAABB->maxXY, BLUE);
        }
       
    }

    App::Print(POSITIONX, POSITIONY, FRAMECOLTEXT.c_str(), COLOR[0], COLOR[2], COLOR[2]);
    App::Print(HEALTHPOSITIONX, HEALTHPOSITIONY, HEALTHTEXT.c_str(), COLOR[0], COLOR[2], COLOR[2]);
#endif
}

void Engine::CollisionSystem::End(CScene* pScene)
{
}

void Engine::CollisionSystem::Cleanup()
{
    
}

void Engine::CollisionSystem::AABBDebug(const Vector2& min, const Vector2& max, const float color[3])
{
    App::DrawLine(min.x, min.y, max.x, min.y, color[0], color[1], color[2]);
    App::DrawLine(max.x, min.y, max.x, max.y, color[0], color[1], color[2]);
    App::DrawLine(max.x, max.y, min.x, max.y, color[0], color[1], color[2]);
    App::DrawLine(min.x, max.y, min.x, min.y, color[0], color[1], color[2]);

}

bool Engine::CollisionSystem::CheckCollision(const sAABB& a, const sAABB& b)
{
    return (a.maxXY.x > b.minXY.x &&
        a.minXY.x < b.maxXY.x &&
        a.maxXY.y > b.minXY.y &&
        a.minXY.y < b.maxXY.y);
}

void Engine::CollisionSystem::ResolveCollision(CScene* pScene, float deltatime)
{

    for (Entity entityA : SComponentIterator<Transform, sAABB, Tag>(*pScene))
    {
        sAABB* aabbA = pScene->GetComponent<sAABB>(entityA);
        Tag* pTag = pScene->GetComponent<Tag>(entityA);

        for (Entity entityB : SComponentIterator<Transform, sAABB, Tag>(*pScene))
        {
            if (entityA == entityB) continue;

            sAABB* aabbB = pScene->GetComponent<sAABB>(entityB);
            Tag* pTag1 = pScene->GetComponent<Tag>(entityB);

           HEALTHTEXT = "HEALTH : " + std::to_string(pScene->GetComponent<HealthComponent>(PlayerUtilities::GetPlayerID(pScene))->currentHealth);

             if (CheckCollision(*aabbA, *aabbB))
             {

                 sCollisionData collData = sCollisionData();
                 collData.pScene = pScene;
                 collData.entityA = entityA;
                 collData.entityB = entityB;

                 bool isNewCollision = FrameCollision(collData);
                 if (!isNewCollision)
                 {

                     continue;

                 }
                 TriggerCollision(collData);


                 if (entityA == PlayerUtilities::GetPlayerID(pScene))
                 {
                     pScene->RemoveEntity(entityB);
                 }



                 // Resolve by moving the entity out of collision
                // Vector2 overlap = aabbA->center - aabbB->center;
                // pScene->GetComponent<Transform>(entityA)->position += overlap * deltatime ;
                // pScene->GetComponent<Transform>(entityB)->position -= overlap * deltatime;

               
                    

                 

             }
             
           
        }

    }


 

}

void Engine::CollisionSystem::CreateAABB(Entity entityID, Rigidbody* pRb, Transform* pTransform, CScene* pScene)
{

    if (pRb->physicsBody == ePhysicsBody::NONE)
    {

    }
    else if(pRb->physicsBody == ePhysicsBody::AABB)
    {
        sAABB* aabb = new sAABB();
        aabb = pScene->AddComponent<sAABB>(entityID);
        aabb->CalculateBounds(*pTransform, Vector2(100.0f, 100.0f));
    }


}

bool Engine::CollisionSystem::FrameCollision(const sCollisionData& collData)
{
    FrameCollisionComponent* pFrameColl = ComponentUtils::GetFrameCollision();
    FrameCounterComponent* pFrames = ComponentUtils::GetFrameCounter();

    int currFrame = pFrames->frameCount % FRAME_RATE;
    bool isNewCollision = pFrameColl->collisions[currFrame].insert(collData).second;

    return isNewCollision;

}

void Engine::CollisionSystem::TriggerCollision(const sCollisionData& collData)
{
    iEventBus<eCollisionEvents, CollisionEnterEvent>* pEventBus = EventBusLocator<eCollisionEvents, CollisionEnterEvent>::Get();

    CollisionEnterEvent collEvent = CollisionEnterEvent();
    collEvent.collisionData = collData;
    pEventBus->Publish(collEvent);

}
