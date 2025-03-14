#include "stdafx.h"
#include "GamplayUtils.h"

#include "src/ECS/SComponents.h"
#include "src/Physics/AABB.h"


#include "src/Utilities/GraphicUtils.h"

namespace Engine
{
	 

	// TODO : Should this be here ? should I create a sprite system and handle the sprite assignment through that ?
	Entity Engine::GamplayUtils::CreateECSTEST(CScene* pScene, Vector2 position)
	{
		Entity ECSTestId = pScene->CreateEntity();
		Transform* pTransform = pScene->AddComponent<Transform>(ECSTestId);
		pTransform->position = position;
		pTransform->rotation = 35;
		pTransform->scale = 3;

		return ECSTestId;
	}


	Entity GamplayUtils::CreateBackground(CScene* pScene, Vector2 position)
	{
		Entity backgroundId = pScene->CreateEntity();
		Transform* pTransform = pScene->AddComponent<Transform>(backgroundId);
		pTransform->position = position;
		pTransform->rotation = 0;
		pTransform->scale = 1;

		SpriteRenderer* pSprite = pScene->AddComponent<SpriteRenderer>(backgroundId);
		pSprite->fileName = "D:/Git Repos/Ubisoft_Next/Ubisoft-NEXT/GameTest/Assets/Backgroound.png";  //TODO : Should Change this
		pSprite->cols = 1;
		pSprite->rows = 1;
		pSprite->animSpeed = 1.0f;

		GraphicUtils::SetupSprite(pSprite, pTransform);

		return backgroundId;

	}
	Entity GamplayUtils::CreatePlayer(CScene* pScene, Vector2 position)
	{
		Entity playerId = pScene->CreateEntity();

		Tag* pTag = pScene->AddComponent<Tag>(playerId);
		pTag->entityName = "Player";

		Transform* pTransform = pScene->AddComponent<Transform>(playerId);
		pTransform->position = position;
		pTransform->rotation = 0;
		pTransform->scale = 1;

		SpriteRenderer* pSprite = pScene->AddComponent<SpriteRenderer>(playerId);
		pSprite->fileName = "D:/Git Repos/Ubisoft_Next/Ubisoft-NEXT/GameTest/Assets/PlayerIdle.png";  //TODO : Should Change this
		pSprite->cols = 5;
		pSprite->rows = 1;
		pSprite->animSpeed = 1.0f;

		GraphicUtils::SetupSprite(pSprite, pTransform);
		/*
		  spritemanager.addanimation(idle, speed, frames);
		  spritemanager.addanimation(forward, speed, frames);
		  spritemanager.addanimation(backward, speed, frames);
		  spritemanager.addanimation(attack, speed, frames);
		  
		  then set the animation in the controller or  something
		
		
		*/

		MovementComponent* pMove = pScene->AddComponent<MovementComponent>(playerId);
		pMove->acceleration = Vector2(0.0f, 0.0f);
		pMove->velocity = Vector2(0.0f, 0.0f);
		pMove->isStatic = false;

		HealthComponent* pHealth = pScene->AddComponent<HealthComponent>(playerId);
		pHealth->currentHealth = pHealth->maxHealth;


		//TODO : For Now Rigidbody is not of big use should change this
		Rigidbody* pRigidbody = pScene->AddComponent<Rigidbody>(playerId);
		pRigidbody->physicsBody = ePhysicsBody::AABB;
		pRigidbody->mass = 1.0f;
		pRigidbody->gravity = -9.8f;
		pRigidbody->isKinematic = false;


		RaycastComponent* pRaycast = pScene->AddComponent<RaycastComponent>(playerId);
		pRaycast->origin = Vector2(0, 0);
		pRaycast->direction = Vector2(0, 0);
		pRaycast->length = 0.0f;
       
		

		return playerId;

	}

	Entity GamplayUtils::CreateCollidable(CScene* pScene, Vector2 position)
	{
		Entity collidableId = pScene->CreateEntity();

		Tag* pTag = pScene->AddComponent<Tag>(collidableId);
		pTag->entityName = "Collide";

		Transform* pTransform = pScene->AddComponent<Transform>(collidableId);
		pTransform->position = position;
		pTransform->rotation = 0;
		pTransform->scale = 1;

		SpriteRenderer* pSprite = pScene->AddComponent<SpriteRenderer>(collidableId);
		pSprite->fileName = "D:/Git Repos/Ubisoft_Next/Ubisoft-NEXT/GameTest/Assets/Attack_1.png";  //TODO : Should Change this
		pSprite->cols = 5;
		pSprite->rows = 1;
		pSprite->animSpeed = 1.0f;

		GraphicUtils::SetupSprite(pSprite, pTransform);

		MovementComponent* pMove = pScene->AddComponent<MovementComponent>(collidableId);
		pMove->acceleration = Vector2(0.0f, 0.0f);
		pMove->velocity = Vector2(0.0f, 0.0f);
		pMove->isStatic = true;


		Rigidbody* pRigidbody = pScene->AddComponent<Rigidbody>(collidableId);
		pRigidbody->physicsBody = ePhysicsBody::AABB;
		pRigidbody->mass = 1.0f;
		pRigidbody->gravity = -9.8f;
		pRigidbody->isKinematic = false;

	

		return collidableId;
	}

	Entity GamplayUtils::CreateCollidable2(CScene* pScene, Vector2 position)
	{
		Entity collidableId = pScene->CreateEntity();

		Tag* pTag = pScene->AddComponent<Tag>(collidableId);
		pTag->entityName = "Collide2";

		Transform* pTransform = pScene->AddComponent<Transform>(collidableId);
		pTransform->position = position;
		pTransform->rotation = 0;
		pTransform->scale = 1;

		SpriteRenderer* pSprite = pScene->AddComponent<SpriteRenderer>(collidableId);
		pSprite->fileName = "D:/Git Repos/Ubisoft_Next/Ubisoft-NEXT/GameTest/Assets/Attack_1.png";  //TODO : Should Change this
		pSprite->cols = 5;
		pSprite->rows = 1;
		pSprite->animSpeed = 1.0f;

		GraphicUtils::SetupSprite(pSprite, pTransform);

		MovementComponent* pMove = pScene->AddComponent<MovementComponent>(collidableId);
		pMove->acceleration = Vector2(0.0f, 0.0f);
		pMove->velocity = Vector2(0.0f, 0.0f);
		pMove->isStatic = true;

		Rigidbody* pRigidbody = pScene->AddComponent<Rigidbody>(collidableId);
		pRigidbody->physicsBody = ePhysicsBody::AABB;
		pRigidbody->mass = 1.0f;
		pRigidbody->gravity = -9.8f;
		pRigidbody->isKinematic = false;

		

		return collidableId;
	}

	Entity GamplayUtils::CreateCamera(CScene* pScene, Vector2 position)
	{
		Entity cameraId = pScene->CreateEntity();

		Transform* pTransform = pScene->AddComponent<Transform>(cameraId);
		pTransform->position = position;
		pTransform->rotation = 0;
		pTransform->scale = 1;

		CameraComponent* pCamera = pScene->AddComponent<CameraComponent>(cameraId);
		pCamera->position = position;


		return cameraId;
	}

	

	

	

	
	
}

