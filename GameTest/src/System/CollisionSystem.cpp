#include "stdafx.h"
#include "CollisionSystem.h"

#include "App/app.h"
#include "src/ECS/SComponentIterator.h"
#include "src/Utilities/PlayerUtilities.h"
#include "src/Utilities/ComponentUtils.h"
#include "src/Events/EventBus.hpp"
#include "src/Events/EventBusLocator.hpp"


namespace Engine
{
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


            CreateAABB(entityId, pRigidbody, pTransform, pScene);
        }

        for (Entity entityId : SComponentIterator<HealthComponent>(*pScene)) // TODO : Should Remove this from here
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
                    collisionNormals.clear();
                
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

        //App::Print(POSITIONX, POSITIONY, FRAMECOLTEXT.c_str(), COLOR[0], COLOR[2], COLOR[2]);
#endif
   // App::Print(HEALTHPOSITIONX, HEALTHPOSITIONY, HEALTHTEXT.c_str(), COLOR[0], COLOR[2], COLOR[2]);
    }

    void Engine::CollisionSystem::End(CScene* pScene)
    {
    }

    void Engine::CollisionSystem::Cleanup()
    {


        collisionNormals.clear();
        activeEntites.clear();
        passiveEntites.clear();

      

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
        Vector2 centerDiff = a.center - b.center;

        float overlapX = Min(a.maxXY.x, b.maxXY.x) - Max(a.minXY.x, b.minXY.x);
        float overlapY = Min(a.maxXY.y, b.maxXY.y) - Max(a.minXY.y, b.minXY.y);

        if (overlapX < overlapY)
        {
            collisionNormals.push_back(Vector2(centerDiff.x < 0 ? -1 : 1, 0)); // X-axis normal
        }
        else
        {
            collisionNormals.push_back(Vector2(0, centerDiff.y < 0 ? -1 : 1)); // Y-axis normal
        }

        return (a.maxXY.x > b.minXY.x &&
            a.minXY.x < b.maxXY.x &&
            a.maxXY.y > b.minXY.y &&
            a.minXY.y < b.maxXY.y);
    }

    void Engine::CollisionSystem::ResolveCollision(CScene* pScene, float deltatime)
    {


        for (Entity& entitesActive : activeEntites)
        {
            sAABB* aabbA = pScene->GetComponent<sAABB>(entitesActive);

            for (Entity& entitesPassive : passiveEntites)
            {
                if (entitesActive == entitesPassive)
                {
                    continue;
                }
                
                    sAABB* aabbB = pScene->GetComponent<sAABB>(entitesPassive);
                    Tag* pTag1 = pScene->GetComponent<Tag>(entitesPassive);
                    if (CheckCollision(*aabbA, *aabbB))
                    {

                        if (collisionNormals.size() > 0)
                        {

                            Vector2 normal = ComputeNormals(collisionNormals);
                            normal = normal.normalized();



                            Vector2 incident = pScene->GetComponent<MovementComponent>(entitesActive)->velocity;
                            float dotProduct = Vector2::Dot(incident, normal);
                            if (dotProduct < 0)
                            {
                                normal = normal * -1;
                                dotProduct = -dotProduct;
                            }

                            Vector2 reflected = Vector2::Reflect(incident, normal);

                            float distancedReflected = reflected.magnitude();
                            if (distancedReflected > 0.001f)
                            {
                                if (pTag1->entityName == "Hole")
                                {
                                    reflected = Vector2(deltatime * 1500, deltatime * 1500);
                                    pScene->RemoveEntity(entitesPassive);
                                    auto it = std::find(passiveEntites.begin(), passiveEntites.end(), entitesPassive);
                                    if (it != passiveEntites.end())
                                    {
                                        passiveEntites.erase(it);
                                    }

                                   /* sCollisionData collData = sCollisionData();
                                    collData.pScene = pScene;
                                    collData.entityA = entitesActive;
                                    collData.entityB = entitesPassive;

                                    bool isNewCollision = FrameCollision(collData);
                                    if (!isNewCollision)
                                    {
                                        continue;
                                    }

                                    TriggerCollision(collData);*/
                                }

                                pScene->GetComponent<MovementComponent>(entitesActive)->velocity = reflected * 2;
                                pScene->GetComponent<MovementComponent>(entitesPassive)->velocity = reflected * 2;
                            }



                        }

                      
                    }
               
              

            }


#if USELESS CODE

            //for (Entity& otherActive : activeEntites)
            //{
            //    if (entitesActive == otherActive) continue;

            //    sAABB* aabbB = pScene->GetComponent<sAABB>(entitesActive);

            //    if (CheckCollision(*aabbA, *aabbB))
            //    {

            //        if (collisionNormals.size() > 0)
            //        {

            //            Vector2 normal = ComputeNormals(collisionNormals);
            //            normal = normal.normalized();



            //            Vector2 incident = pScene->GetComponent<MovementComponent>(entitesActive)->velocity;
            //            float dotProduct = Vector2::Dot(incident, normal);
            //            if (dotProduct < 0)
            //            {
            //                normal = normal * -1;
            //                dotProduct = -dotProduct;
            //            }

            //            Vector2 reflected = Vector2::Reflect(incident, normal);

            //            float distancedReflected = reflected.magnitude();
            //            if (distancedReflected > 0.001f)
            //            {
            //                /*if (pTag1->entityName == "Collide2")
            //                {
            //                    reflected = Vector2(deltatime * 1500, deltatime * 1500);
            //                    pScene->RemoveEntity(entityB);
            //                }*/

            //                pScene->GetComponent<MovementComponent>(entitesActive)->velocity = reflected * 2;
            //                pScene->GetComponent<MovementComponent>(otherActive)->velocity = reflected * 2;
            //            }



            //        }
            //    }

            //}

#endif // USELESS CODE

            



        }



    }

    void Engine::CollisionSystem::CreateAABB(Entity entityID, Rigidbody* pRb, Transform* pTransform, CScene* pScene)
    {

        if (pRb->physicsBody == ePhysicsBody::NONE)
        {
            //No Collider
        }
        else if (pRb->physicsBody == ePhysicsBody::AABB && pRb->physicsType == ePhysicsType::ACTIVE)
        {
            sAABB* aabb = new sAABB();
            aabb = pScene->AddComponent<sAABB>(entityID);
            aabb->CalculateBounds(*pTransform, pRb->colliderSize);
            activeEntites.push_back(entityID);

        }

        else if (pRb->physicsBody == ePhysicsBody::AABB && pRb->physicsType == ePhysicsType::PASSIVE)
        {
            sAABB* aabb = new sAABB();
            aabb = pScene->AddComponent<sAABB>(entityID);
            aabb->CalculateBounds(*pTransform, pRb->colliderSize);
            passiveEntites.push_back(entityID);

        }


    }

    bool Engine::CollisionSystem::FrameCollision(const sCollisionData& collData)
    {
        FrameCollisionComponent* pFrameColl = ComponentUtils::GetFrameCollision();
        FrameCounterComponent* pFrames = ComponentUtils::GetFrameCounter();

        int currFrame = pFrames->frameCount % FRAME_RATE;
        bool isNewCollision = pFrameColl->collisions[currFrame].insert(collData).second;
        //pFrameColl->collisions[currFrame].clear();
        return isNewCollision;

    }

    void Engine::CollisionSystem::TriggerCollision(const sCollisionData& collData)
    {
        iEventBus<eCollisionEvents, CollisionEnterEvent>* pEventBus = EventBusLocator<eCollisionEvents, CollisionEnterEvent>::Get();

        CollisionEnterEvent collEvent = CollisionEnterEvent();
        collEvent.collisionData = collData;
        pEventBus->Publish(collEvent);

    }

    Vector2 Engine::CollisionSystem::ComputeNormals(std::vector<Vector2> collisionNormals)
    {
        Vector2 normal = Vector2(0,0);
        for (const auto& n : collisionNormals)
        {

            normal = normal + n;
        }
        normal = normal / static_cast<float>(collisionNormals.size());

        return normal;
    }

    void CollisionSystem::ResolveCollisionWithNormals(CScene* pScene, Entity entities)
    {

        if (collisionNormals.size() > 0)
        {

            Vector2 normal = ComputeNormals(collisionNormals);
            normal = normal.normalized();



            Vector2 incident = pScene->GetComponent<MovementComponent>(entities)->velocity;
            float dotProduct = Vector2::Dot(incident, normal);
            if (dotProduct < 0)
            {
                normal = normal * -1;
                dotProduct = -dotProduct;
            }

            Vector2 reflected = Vector2::Reflect(incident, normal);

            float distancedReflected = reflected.magnitude();
            if (distancedReflected > 0.001f)
            {
                /*if (pTag1->entityName == "Collide2")
                {
                    reflected = Vector2(deltatime * 1500, deltatime * 1500);
                    pScene->RemoveEntity(entitesActive);
                }*/

                pScene->GetComponent<MovementComponent>(entities)->velocity = reflected * 1;

            }



        }
    }


}
