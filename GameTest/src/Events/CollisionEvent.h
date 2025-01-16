#pragma once

#include "Event.hpp"
#include "src/System/Debug/PhysicsProperties.h"

namespace Engine
{
	enum eCollisionEvents
	{
		ONCOLLISION_ENTER,
		ONCOLLISION_EXIT
	};

	class CollisionEnterEvent : public Event<eCollisionEvents>
	{
	public:
		CollisionEnterEvent() :
			Event<eCollisionEvents>(eCollisionEvents::ONCOLLISION_ENTER, "OnCollisionEnter") {};
		virtual ~CollisionEnterEvent() {};

		sCollisionData collisionData;
	};

	class CollisionExitEvent : public Event<eCollisionEvents>
	{
	public:
		CollisionExitEvent() :
			Event<eCollisionEvents>(eCollisionEvents::ONCOLLISION_EXIT, "OnCollisionEnter") {};
		virtual ~CollisionExitEvent() {};

		Entity entityA;
		Entity entityB;
	};
}
