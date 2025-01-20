#include "stdafx.h"
#include "GamplayUtils.h"

#include "src/ECS/SComponents.h"
#include "src/Physics/AABB.h"
#include <random>

#include "src/Utilities/GraphicUtils.h"

namespace Engine
{
	 

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
		pSprite->fileName = "D:/Git Repos/Ubisoft_Next/Ubisoft-NEXT/GameTest/Assets/LevelOneBG.png";  
		pSprite->cols = 1;
		pSprite->rows = 1;
		pSprite->animSpeed = 1.0f;
		pSprite->isVisible = true;

		GraphicUtils::SetupSprite(pSprite, pTransform);

		return backgroundId;

	}

	Entity GamplayUtils::CreateFogOfWar(CScene* pScene, Vector2 position)
	{
		Entity backgroundId = pScene->CreateEntity();
		Transform* pTransform = pScene->AddComponent<Transform>(backgroundId);
		pTransform->position = position;
		pTransform->rotation = 0;
		pTransform->scale = 1;

		FogOfWarComponent* pFogOfWar = pScene->AddComponent<FogOfWarComponent>(backgroundId);
		pFogOfWar->centre = Vector2(0, 0);
		pFogOfWar->targetPos = Vector2(0, 0);

		SpriteRenderer* pSprite = pScene->AddComponent<SpriteRenderer>(backgroundId);
		pSprite->fileName = ".\\Assets\\FogOfWar.png";
		pSprite->cols = 1;
		pSprite->rows = 1;
		pSprite->animSpeed = 1.0f;
		pSprite->isVisible = false;

		GraphicUtils::SetupSprite(pSprite, pTransform);

		return backgroundId;;
	}

	Entity GamplayUtils::CreateTitle(CScene* pScene, Vector2 position)
	{
		Entity backgroundId = pScene->CreateEntity();
		Transform* pTransform = pScene->AddComponent<Transform>(backgroundId);
		pTransform->position = position;
		pTransform->rotation = 0;
		pTransform->scale = 1;

		SpriteRenderer* pSprite = pScene->AddComponent<SpriteRenderer>(backgroundId);
		pSprite->fileName = ".\\Assets\\Title.png";
		pSprite->cols = 1;
		pSprite->rows = 1;
		pSprite->animSpeed = 1.0f;
		pSprite->isVisible = true;

		GraphicUtils::SetupSprite(pSprite, pTransform);

		return backgroundId;;
	}

	Entity GamplayUtils::CreateGameOver(CScene* pScene, Vector2 position)
	{
		Entity backgroundId = pScene->CreateEntity();
		Transform* pTransform = pScene->AddComponent<Transform>(backgroundId);
		pTransform->position = position;
		pTransform->rotation = 0;
		pTransform->scale = 1;

		SpriteRenderer* pSprite = pScene->AddComponent<SpriteRenderer>(backgroundId);
		pSprite->fileName = ".\\Assets\\GameOver.png";
		pSprite->cols = 1;
		pSprite->rows = 1;
		pSprite->animSpeed = 1.0f;
		pSprite->isVisible = true;

		GraphicUtils::SetupSprite(pSprite, pTransform);

		return backgroundId;;
	}

	Entity GamplayUtils::CreatePlayer(CScene* pScene, Vector2 position)
	{
		Entity playerId = pScene->CreateEntity();

		Tag* pTag = pScene->AddComponent<Tag>(playerId);
		pTag->entityName = "Player";

		Transform* pTransform = pScene->AddComponent<Transform>(playerId);
		pTransform->position = position;
		pTransform->rotation = 0;
		pTransform->scale = 0.75f;

		SpriteRenderer* pSprite = pScene->AddComponent<SpriteRenderer>(playerId);
		pSprite->fileName = ".\\Assets\\Golf.png";  //TODO : Should Change this
		pSprite->cols = 1;
		pSprite->rows = 1;
		pSprite->animSpeed = 1.0f;
		pSprite->isVisible = true;

		GraphicUtils::SetupSprite(pSprite, pTransform);
		

		MovementComponent* pMove = pScene->AddComponent<MovementComponent>(playerId);
		pMove->acceleration = Vector2(0.0f, 0.0f);
		pMove->velocity = Vector2(0.0f, 0.0f);
		pMove->drag = 1000.0f;
		pMove->isStatic = false;

		HealthComponent* pHealth = pScene->AddComponent<HealthComponent>(playerId);
		pHealth->currentHealth = pHealth->maxHealth;

		ScoreComponent* pScore = pScene->AddComponent<ScoreComponent>(playerId);
		pScore->strokes = 0;
		pScore->maxStrokes = 6;
		pScore->multiplier = 15;
		pScore->isGoal = false;


		//TODO : For Now Rigidbody is not of big use should change this
		Rigidbody* pRigidbody = pScene->AddComponent<Rigidbody>(playerId);
		pRigidbody->physicsBody = ePhysicsBody::AABB;
		pRigidbody->physicsType = ePhysicsType::ACTIVE;
		pRigidbody->colliderSize = Vector2(30, 30);
		pRigidbody->isKinematic = false;
		pRigidbody->useGravity = false;


		RaycastComponent* pRaycast = pScene->AddComponent<RaycastComponent>(playerId);
		pRaycast->origin = Vector2(0, 0);
		pRaycast->direction = Vector2(0, 0);
		pRaycast->length = 0.0f;
       
		

		return playerId;

	}

	Entity GamplayUtils::CreatePlayer2(CScene* pScene, Vector2 position)
	{
		Entity playerId = pScene->CreateEntity();

		Tag* pTag = pScene->AddComponent<Tag>(playerId);
		pTag->entityName = "Player";

		Transform* pTransform = pScene->AddComponent<Transform>(playerId);
		pTransform->position = position;
		pTransform->rotation = 0;
		pTransform->scale = 1;

		SpriteRenderer* pSprite = pScene->AddComponent<SpriteRenderer>(playerId);
		pSprite->fileName = ".\\Assets\\golf.png";  //TODO : Should Change this
		pSprite->cols = 1;
		pSprite->rows = 1;
		pSprite->animSpeed = 1.0f;

		GraphicUtils::SetupSprite(pSprite, pTransform);


		MovementComponent* pMove = pScene->AddComponent<MovementComponent>(playerId);
		pMove->acceleration = Vector2(0.0f, 0.0f);
		pMove->velocity = Vector2(0.0f, 0.0f);
		pMove->isStatic = false;

		HealthComponent* pHealth = pScene->AddComponent<HealthComponent>(playerId);
		pHealth->currentHealth = pHealth->maxHealth;


		//TODO : For Now Rigidbody is not of big use should change this
		Rigidbody* pRigidbody = pScene->AddComponent<Rigidbody>(playerId);
		pRigidbody->physicsBody = ePhysicsBody::AABB;
		pRigidbody->physicsType = ePhysicsType::ACTIVE;
		pRigidbody->colliderSize = Vector2(30, 30);
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
		pTag->entityName = "Block";

		Transform* pTransform = pScene->AddComponent<Transform>(collidableId);
		pTransform->position = position;
		pTransform->rotation = 0;
		pTransform->scale = 0.75f;

		SpriteRenderer* pSprite = pScene->AddComponent<SpriteRenderer>(collidableId);
		pSprite->fileName = ".\\Assets\\Block.png";  //TODO : Should Change this
		pSprite->cols = 1;
		pSprite->rows = 1;
		pSprite->animSpeed = 1.0f;
		pSprite->isVisible = true;
		GraphicUtils::SetupSprite(pSprite, pTransform);
		pSprite->isStatic = true;

		MovementComponent* pMove = pScene->AddComponent<MovementComponent>(collidableId);
		pMove->acceleration = Vector2(0.0f, 0.0f);
		pMove->velocity = Vector2(0.0f, 0.0f);
		pMove->isStatic = true;
		
	
		Rigidbody* pRigidbody = pScene->AddComponent<Rigidbody>(collidableId);
		pRigidbody->physicsBody = ePhysicsBody::AABB;
		pRigidbody->physicsType = ePhysicsType::ACTIVE;
		pRigidbody->colliderSize = Vector2(50, 50);
		pRigidbody->mass = 1.0f;
		pRigidbody->gravity = -9.8f;
		pRigidbody->isKinematic = true;

	

		return collidableId;
	}

	Entity GamplayUtils::CreateCollidable2(CScene* pScene, Vector2 position)
	{
		Entity collidableId = pScene->CreateEntity();

		Tag* pTag = pScene->AddComponent<Tag>(collidableId);
		pTag->entityName = "Block";

		Transform* pTransform = pScene->AddComponent<Transform>(collidableId);
		pTransform->position = position;
		pTransform->rotation = 0;
		pTransform->scale = 0.75f;

		SpriteRenderer* pSprite = pScene->AddComponent<SpriteRenderer>(collidableId);
		pSprite->fileName = ".\\Assets\\BlockTwo.png";  //TODO : Should Change this
		pSprite->cols = 1;
		pSprite->rows = 1;
		pSprite->animSpeed = 1.0f;
		pSprite->isVisible = true;
		GraphicUtils::SetupSprite(pSprite, pTransform);
		pSprite->isStatic = true;

		MovementComponent* pMove = pScene->AddComponent<MovementComponent>(collidableId);
		pMove->acceleration = Vector2(0.0f, 0.0f);
		pMove->velocity = Vector2(0.0f, 0.0f);
		pMove->isStatic = true;


		Rigidbody* pRigidbody = pScene->AddComponent<Rigidbody>(collidableId);
		pRigidbody->physicsBody = ePhysicsBody::AABB;
		pRigidbody->physicsType = ePhysicsType::ACTIVE;
		pRigidbody->colliderSize = Vector2(50, 95);
		pRigidbody->mass = 1.0f;
		pRigidbody->gravity = -9.8f;
		pRigidbody->isKinematic = true;



		return collidableId;
	}

	Entity GamplayUtils::CreateCollidable3(CScene* pScene, Vector2 position)
	{
		Entity collidableId = pScene->CreateEntity();

		Tag* pTag = pScene->AddComponent<Tag>(collidableId);
		pTag->entityName = "Block";

		Transform* pTransform = pScene->AddComponent<Transform>(collidableId);
		pTransform->position = position;
		pTransform->rotation = 0;
		pTransform->scale = 0.75f;

		SpriteRenderer* pSprite = pScene->AddComponent<SpriteRenderer>(collidableId);
		pSprite->fileName = ".\\Assets\\BlockThree.png";  //TODO : Should Change this
		pSprite->cols = 1;
		pSprite->rows = 1;
		pSprite->animSpeed = 1.0f;
		pSprite->isVisible = true;
		GraphicUtils::SetupSprite(pSprite, pTransform);
		pSprite->isStatic = true;

		MovementComponent* pMove = pScene->AddComponent<MovementComponent>(collidableId);
		pMove->acceleration = Vector2(0.0f, 0.0f);
		pMove->velocity = Vector2(0.0f, 0.0f);
		pMove->isStatic = true;


		Rigidbody* pRigidbody = pScene->AddComponent<Rigidbody>(collidableId);
		pRigidbody->physicsBody = ePhysicsBody::AABB;
		pRigidbody->physicsType = ePhysicsType::ACTIVE;
		pRigidbody->colliderSize = Vector2(95, 50);
		pRigidbody->mass = 1.0f;
		pRigidbody->gravity = -9.8f;
		pRigidbody->isKinematic = true;



		return collidableId;
	}

	Entity GamplayUtils::CreateWall(CScene* pScene, Vector2 position)
	{
		Entity collidableId = pScene->CreateEntity();

		Tag* pTag = pScene->AddComponent<Tag>(collidableId);
		pTag->entityName = "Block";

		Transform* pTransform = pScene->AddComponent<Transform>(collidableId);
		pTransform->position = position;
		pTransform->rotation = 0;
		pTransform->scale = 0.75f;

		SpriteRenderer* pSprite = pScene->AddComponent<SpriteRenderer>(collidableId);
		pSprite->fileName = ".\\Assets\\Wall.png";  //TODO : Should Change this
		pSprite->cols = 1;
		pSprite->rows = 1;
		pSprite->animSpeed = 1.0f;
		pSprite->isVisible = true;
		GraphicUtils::SetupSprite(pSprite, pTransform);
		pSprite->isStatic = true;

		MovementComponent* pMove = pScene->AddComponent<MovementComponent>(collidableId);
		pMove->acceleration = Vector2(0.0f, 0.0f);
		pMove->velocity = Vector2(0.0f, 0.0f);
		pMove->isStatic = true;


		Rigidbody* pRigidbody = pScene->AddComponent<Rigidbody>(collidableId);
		pRigidbody->physicsBody = ePhysicsBody::AABB;
		pRigidbody->physicsType = ePhysicsType::ACTIVE;
		pRigidbody->colliderSize = Vector2(50, 330);
		pRigidbody->mass = 1.0f;
		pRigidbody->gravity = -9.8f;
		pRigidbody->isKinematic = true;


		return collidableId;
	}

	Entity GamplayUtils::CreateWall2(CScene* pScene, Vector2 position)
	{
		Entity collidableId = pScene->CreateEntity();

		Tag* pTag = pScene->AddComponent<Tag>(collidableId);
		pTag->entityName = "Block";

		Transform* pTransform = pScene->AddComponent<Transform>(collidableId);
		pTransform->position = position;
		pTransform->rotation = 0;
		pTransform->scale = 0.75f;

		SpriteRenderer* pSprite = pScene->AddComponent<SpriteRenderer>(collidableId);
		pSprite->fileName = ".\\Assets\\Wall2.png";  //TODO : Should Change this
		pSprite->cols = 1;
		pSprite->rows = 1;
		pSprite->animSpeed = 1.0f;
		pSprite->isVisible = true;
		GraphicUtils::SetupSprite(pSprite, pTransform);
		pSprite->isStatic = true;

		MovementComponent* pMove = pScene->AddComponent<MovementComponent>(collidableId);
		pMove->acceleration = Vector2(0.0f, 0.0f);
		pMove->velocity = Vector2(0.0f, 0.0f);
		pMove->isStatic = true;


		Rigidbody* pRigidbody = pScene->AddComponent<Rigidbody>(collidableId);
		pRigidbody->physicsBody = ePhysicsBody::AABB;
		pRigidbody->physicsType = ePhysicsType::ACTIVE;
		pRigidbody->colliderSize = Vector2(765, 50);
		pRigidbody->mass = 1.0f;
		pRigidbody->gravity = -9.8f;
		pRigidbody->isKinematic = true;


		return collidableId;
	}

	Entity GamplayUtils::CreateGoal(CScene* pScene, Vector2 position)
	{
		Entity goalId = pScene->CreateEntity();

		Tag* pTag = pScene->AddComponent<Tag>(goalId);
		pTag->entityName = "Goal";

		Transform* pTransform = pScene->AddComponent<Transform>(goalId);
		pTransform->position = position;
		pTransform->rotation = 0;
		pTransform->scale = 0.15f;

		SpriteRenderer* pSprite = pScene->AddComponent<SpriteRenderer>(goalId);
		pSprite->fileName = ".\\Assets\\Hole.png";  //TODO : Should Change this
		pSprite->cols = 1;
		pSprite->rows = 1;
		pSprite->animSpeed = 1.0f;
		pSprite->isVisible = true;
		GraphicUtils::SetupSprite(pSprite, pTransform);
		pSprite->isStatic = true;
		

		MovementComponent* pMove = pScene->AddComponent<MovementComponent>(goalId);
		pMove->acceleration = Vector2(0.0f, 0.0f);
		pMove->velocity = Vector2(0.0f, 0.0f);
		pMove->isStatic = true;


		Rigidbody* pRigidbody = pScene->AddComponent<Rigidbody>(goalId);
		pRigidbody->physicsBody = ePhysicsBody::AABB;
		pRigidbody->physicsType = ePhysicsType::PASSIVE;
		pRigidbody->colliderSize = Vector2(20, 20);
		pRigidbody->mass = 1.0f;
		pRigidbody->gravity = -9.8f;
		pRigidbody->isKinematic = true;



		return goalId;
	}

	Entity GamplayUtils::CreateRed(CScene* pScene, Vector2 position)
	{
		Entity redBallId = pScene->CreateEntity();

		Tag* pTag = pScene->AddComponent<Tag>(redBallId);
		pTag->entityName = "Red";

		Transform* pTransform = pScene->AddComponent<Transform>(redBallId);
		pTransform->position = position;
		pTransform->rotation = 0;
		pTransform->scale = 0.75f;

		SpriteRenderer* pSprite = pScene->AddComponent<SpriteRenderer>(redBallId);
		pSprite->fileName = ".\\Assets\\Red.png";  //TODO : Should Change this
		pSprite->cols = 1;
		pSprite->rows = 1;
		pSprite->animSpeed = 1.0f;
		pSprite->isVisible = true;

		GraphicUtils::SetupSprite(pSprite, pTransform);
		//pSprite->isStatic = true;

		MovementComponent* pMove = pScene->AddComponent<MovementComponent>(redBallId);
		pMove->acceleration = Vector2(0.0f, 0.0f);
		pMove->velocity = Vector2(0.0f, 0.0f);
		pMove->isStatic = true;


		Rigidbody* pRigidbody = pScene->AddComponent<Rigidbody>(redBallId);
		pRigidbody->physicsBody = ePhysicsBody::AABB;
		pRigidbody->physicsType = ePhysicsType::PASSIVE;
		pRigidbody->colliderSize = Vector2(20, 20);
		pRigidbody->mass = 1.0f;
		pRigidbody->gravity = -9.8f;
		pRigidbody->isKinematic = true;



		return redBallId;
	}

	Entity GamplayUtils::CreateBlue(CScene* pScene, Vector2 position)
	{
		Entity blueBallId = pScene->CreateEntity();

		Tag* pTag = pScene->AddComponent<Tag>(blueBallId);
		pTag->entityName = "Blue";

		Transform* pTransform = pScene->AddComponent<Transform>(blueBallId);
		pTransform->position = position;
		pTransform->rotation = 0;
		pTransform->scale = 0.75f;

		SpriteRenderer* pSprite = pScene->AddComponent<SpriteRenderer>(blueBallId);
		pSprite->fileName = ".\\Assets\\Blue.png";  //TODO : Should Change this
		pSprite->cols = 1;
		pSprite->rows = 1;
		pSprite->animSpeed = 1.0f;
		GraphicUtils::SetupSprite(pSprite, pTransform);
		//pSprite->isStatic = true;
		pSprite->isVisible = true;

		MovementComponent* pMove = pScene->AddComponent<MovementComponent>(blueBallId);
		pMove->acceleration = Vector2(0.0f, 0.0f);
		pMove->velocity = Vector2(0.0f, 0.0f);
		pMove->isStatic = true;


		Rigidbody* pRigidbody = pScene->AddComponent<Rigidbody>(blueBallId);
		pRigidbody->physicsBody = ePhysicsBody::AABB;
		pRigidbody->physicsType = ePhysicsType::PASSIVE;
		pRigidbody->colliderSize = Vector2(20, 20);
		pRigidbody->mass = 1.0f;
		pRigidbody->gravity = -9.8f;
		pRigidbody->isKinematic = true;



		return blueBallId;
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

	Entity GamplayUtils::CreateHole(CScene* pScene, Vector2 position)
	{
		Entity holeId = pScene->CreateEntity();

		Tag* pTag = pScene->AddComponent<Tag>(holeId);
		pTag->entityName = "Hole";

		Transform* pTransform = pScene->AddComponent<Transform>(holeId);
		pTransform->position = position;
		pTransform->rotation = 0;
		pTransform->scale = 0.15f;

		ShuffleHoleComponent* pHole = pScene->AddComponent<ShuffleHoleComponent>(holeId);
		pHole->position = Vector2(0, 0);
		pHole->targetPosition = Vector2(0, 0);
		pHole->isMoving = false;
		pHole->speed = 0;

		MovementComponent* pMove = pScene->AddComponent<MovementComponent>(holeId);
		pMove->acceleration = Vector2(0.0f, 0.0f);
		pMove->velocity = Vector2(0.0f, 0.0f);
		pMove->isStatic = true;

		SpriteRenderer* pSprite = pScene->AddComponent<SpriteRenderer>(holeId);
		pSprite->fileName = ".\\Assets\\Hole.png";  //TODO : Should Change this
		pSprite->cols = 1;
		pSprite->rows = 1;
		pSprite->animSpeed = 1.0f;

		GraphicUtils::SetupSprite(pSprite, pTransform);

		Rigidbody* pRigidbody = pScene->AddComponent<Rigidbody>(holeId);
		pRigidbody->physicsBody = ePhysicsBody::AABB;
		pRigidbody->physicsType = ePhysicsType::ACTIVE;
		pRigidbody->colliderSize = Vector2(50, 50);
		pRigidbody->mass = 1.0f;
		pRigidbody->gravity = -9.8f;
		pRigidbody->isKinematic = true;

		return holeId;

	}

	
	
}

