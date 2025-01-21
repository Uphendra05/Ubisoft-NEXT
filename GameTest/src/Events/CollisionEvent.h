#pragma once
#ifndef _COLLISIONEVENT_H
#define _COLLISIONEVENT_H

#include "Event.hpp"
#include "src/Physics/PhysicsProperties.h"

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
		CollisionEnterEvent() : Event<eCollisionEvents>(eCollisionEvents::ONCOLLISION_ENTER, "OnCollisionEnter") {};

		virtual ~CollisionEnterEvent() {};

		sCollisionData collisionData = sCollisionData();
	};

	class CollisionExitEvent : public Event<eCollisionEvents>
	{
	public:
		CollisionExitEvent() : Event<eCollisionEvents>(eCollisionEvents::ONCOLLISION_EXIT, "OnCollisionEnter") {};

		virtual ~CollisionExitEvent() {};

		Entity entityA = 0;
		Entity entityB = 0;
	};
}
#endif