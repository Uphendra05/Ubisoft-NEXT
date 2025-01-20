#pragma once
#ifndef _SCOMPONENTS_H
#define _SCOMPONENTS_H

#include "ECSCore.h"
#include "../Utilities/Vector2.h"
#include "App/SimpleSprite.h"
#include "App/AppSettings.h"
#include "src/Physics/PhysicsProperties.h"
#include <set>
#include "src/Gamplay/Enums.h"

const int   FRAME_RATE = 60;  // Frames per second
namespace Engine
{
	enum ePhysicsBody  
	{
		NONE =0,
		AABB =1,

	};

	enum ePhysicsType
	{
		ACTIVE = 0,
		PASSIVE = 1,
	};

	struct Tag
	{
		std::string entityName;
		
	};

	struct Transform
	{
		std::string componenetName = "Transform";

		Vector2 position = Vector2(0,0);
		float rotation = 0.0f;
		float scale = 1.0f;

		Vector2 worldPosition = Vector2(0,0);
		float worldrotation = 0.0f;
		float worldScale = 1.0f;

	};

	struct SpriteRenderer
	{
		bool isVisible;
		std::string componenetName = "SpriteRenderer";

		std::string fileName;
		int rows = 0;
		int cols = 0;

		float animSpeed = 0.0f;

		CSimpleSprite* sprite;
		bool isStatic;
	};

	struct MovementComponent
	{
		std::string componenetName = "MovementComponent";

		Vector2 velocity;
		Vector2 acceleration;

		float drag = 10.0f;

		float maxSpeed = 0.0f;
		float maxAcceleration = 0.0f;

		bool isStatic;


		bool isCharging = false;   // Is the player charging a shot?
		float chargePower = 0.0f;  // Current shot power
		float maxPower = 500.0f;   // Maximum shot power
		float chargeRate = 100.0f; // Rate of power increase per second


	};

	struct ScoreComponent
	{
		size_t strokes;
		size_t maxStrokes;
		size_t multiplier;
		bool isGoal;

	};

	struct RotationComponent
	{
		std::string componentName = "RotationComponent";

		float angle;

		float rotationSpeed;

	};

	struct Rigidbody
	{
	public:
		std::string componentName = "Rigibody";
		
		float mass;
		float gravity;
		ePhysicsBody physicsBody;
		ePhysicsType physicsType;
		bool isKinematic;
		bool useGravity;
		Vector2 colliderSize = Vector2(100, 100);

	};

	struct CameraComponent
	{
		Vector2 position = Vector2(0, 0); // Camera position
		float zoom = 1.0f;                // Zoom level
		float width = APP_VIRTUAL_WIDTH ; // Viewport width
		float height = APP_VIRTUAL_HEIGHT ; // Viewport height
	};

	struct HealthComponent
	{
		std::string componentName = "HealthComponent";

		int currentHealth;
		int maxHealth;
	};

	struct RaycastComponent
	{
		Vector2 origin;
		Vector2 direction;
		float length;
	};


	struct FrameCollisionComponent
	{
		std::set<sCollisionData> collisions[FRAME_RATE];
		size_t currSize;
	};

	struct FrameCounterComponent
	{
		int frameCount;
		float fpsTimer;
		float fps;
	};

	struct ShuffleHoleComponent
	{
		Vector2 position = Vector2(0,0);
		Vector2 targetPosition = Vector2(0,0);
		bool isMoving = false;
		float speed = 2000.0f;

	};

	struct GameStateComponent
	{
		eGameStates prevState; // Only state system should modify this
		eGameStates currState; // Any system can modify this to stop/run simulation
	};

}
#endif